import torch
import math
import time
import torch.nn as nn
import numpy as np
import matplotlib.pyplot as plt
from BahdanauAttention import BahdanauAttention
from EncoderDecoder import EncoderDecoder
from Encoder import Encoder
from Decoder import Decoder
from Generator import Generator
from Batch import Batch
from SimpleLossCompute import SimpleLossCompute


MAX_LENGTH = 10  # Maximum sentence length

# Default word tokens
PAD_TOKEN = 0
SOS_TOKEN = 1
EOS_TOKEN = 2
UNK_TOKEN = 3

# set seeds
seed = 1111
np.random.seed(seed)
torch.manual_seed(seed)
torch.cuda.manual_seed(seed)
USE_CUDA = torch.cuda.is_available()


def make_model(src_vocab, tgt_vocab, emb_size=256, hidden_size=512, num_layers=1, dropout=0.1):
    "Helper: Construct a model from hyperparameters."

    attention = BahdanauAttention(hidden_size)

    model = EncoderDecoder(
        Encoder(emb_size, hidden_size, num_layers=num_layers, dropout=dropout),
        Decoder(emb_size, hidden_size, attention, num_layers=num_layers, dropout=dropout),
        nn.Embedding(src_vocab, emb_size),
        nn.Embedding(tgt_vocab, emb_size),
        Generator(hidden_size, tgt_vocab))

    return model.cuda() if USE_CUDA else model


def run_epoch(data_iter, model, loss_compute, print_every=50):
    """Standard Training and Logging Function"""

    start = time.time()
    total_tokens = 0
    total_loss = 0
    print_tokens = 0

    for i, batch in enumerate(data_iter, 1):
        out, _, pre_output = model.forward(batch.src, batch.trg,
            batch.src_mask, batch.trg_mask,
            batch.src_lengths, batch.trg_lengths)
        loss = loss_compute(pre_output, batch.trg_y, batch.nseqs)
        total_loss += loss
        total_tokens += batch.ntokens
        print_tokens += batch.ntokens

        if model.training and i % print_every == 0:
            elapsed = time.time() - start
            print("Epoch Step: %d Loss: %f Tokens per Sec: %f" %
                  (i, loss / batch.nseqs, print_tokens / elapsed))
            start = time.time()
            print_tokens = 0

    return math.exp(total_loss / float(total_tokens))


def data_gen(num_words=11, batch_size=16, num_batches=100, length=10, pad_index=0, sos_index=1):
    """Generate random data for a src-tgt copy task."""
    for i in range(num_batches):
        data = torch.from_numpy(
          np.random.randint(1, num_words, size=(batch_size, length)))
        data[:, 0] = sos_index
        data = data.cuda() if USE_CUDA else data
        src = data[:, 1:]
        trg = data
        src_lengths = [length-1] * batch_size
        trg_lengths = [length] * batch_size
        yield Batch((src, src_lengths), (trg, trg_lengths), pad_index=pad_index)


def greedy_decode(model, src, src_mask, src_lengths, max_len=100, sos_index=1,
        eos_index=None):
    """Greedily decode a sentence."""

    with torch.no_grad():
        encoder_hidden, encoder_final = model.encode(src, src_mask,
            src_lengths)
        prev_y = torch.ones(1, 1).fill_(sos_index).type_as(src)
        trg_mask = torch.ones_like(prev_y)

    output = []
    attention_scores = []
    hidden = None

    for i in range(max_len):
        with torch.no_grad():
            out, hidden, pre_output = model.decode(
                encoder_hidden, encoder_final, src_mask,
                prev_y, trg_mask, hidden)

            # we predict from the pre-output layer, which is
            # a combination of Decoder state, prev emb, and context
            prob = model.generator(pre_output[:, -1])

        _, next_word = torch.max(prob, dim=1)
        next_word = next_word.data.item()
        output.append(next_word)
        prev_y = torch.ones(1, 1).type_as(src).fill_(next_word)
        attention_scores.append(model.decoder.attention.alphas.cpu().numpy())

    output = np.array(output)

    # cut off everything starting from </s>
    # (only when eos_index provided)
    if eos_index is not None:
        first_eos = np.where(output == eos_index)[0]
        if len(first_eos) > 0:
            output = output[:first_eos[0]]

    return output, np.concatenate(attention_scores, axis=1)


def lookup_words(x, vocab=None):
    if vocab is not None:
        x = [vocab.itos[i] for i in x]

    return [str(t) for t in x]


def print_examples(example_iter, model, n=2, max_len=100,
        sos_index=1,
        src_eos_index=None,
        trg_eos_index=None,
        src_vocab=None, trg_vocab=None):
    """Prints N examples. Assumes batch size of 1."""

    model.eval()
    count = 0
    print()

    if src_vocab is not None and trg_vocab is not None:
        src_eos_index = src_vocab.stoi[EOS_TOKEN]
        trg_sos_index = trg_vocab.stoi[SOS_TOKEN]
        trg_eos_index = trg_vocab.stoi[EOS_TOKEN]
    else:
        src_eos_index = None
        trg_sos_index = 1
        trg_eos_index = None

    for i, batch in enumerate(example_iter):

        src = batch.src.cpu().numpy()[0, :]
        trg = batch.trg_y.cpu().numpy()[0, :]

        # remove </s> (if it is there)
        src = src[:-1] if src[-1] == src_eos_index else src
        trg = trg[:-1] if trg[-1] == trg_eos_index else trg

        result, _ = greedy_decode(
            model, batch.src, batch.src_mask, batch.src_lengths,
            max_len=max_len, sos_index=trg_sos_index, eos_index=trg_eos_index)
        print("Example #%d" % (i + 1))
        print("Src : ", " ".join(lookup_words(src, vocab=src_vocab)))
        print("Trg : ", " ".join(lookup_words(trg, vocab=trg_vocab)))
        print("Pred: ", " ".join(lookup_words(result, vocab=trg_vocab)))
        print()

        count += 1
        if count == n:
            break


def train_copy_task():
    """Train the simple copy task."""
    num_words = 11
    batch_size = 32
    epochs = 20
    input_seq_length = 10

    # create a model
    model = make_model(num_words, num_words, emb_size=32, hidden_size=64)
    # loss function and optimizer
    criterion = nn.NLLLoss(reduction="sum", ignore_index=0)
    optim = torch.optim.Adam(model.parameters(), lr=0.0003)

    # data used for evaluation, length of 100, each item is a Batch object
    # eval_data[0] -> a Batch object
    #   eval_data[0].src -> tensor, shape [batch_size, input_seq_length-1]
    #   eval_data[0].src_lengths -> list, [input_seq_length-1] * batch_size
    #   eval_data[0].src_mask -> tensor, shape of [batch_size, 1, input_seq_length-1]
    #   eval_data[0].trg -> tensor, shape [batch_size, input_seq_length-1]
    #   eval_data[0].trg_lengths -> list, [input_seq_length-1] * batch_size
    #   eval_data[0].trg_mask -> tensor, shape [batch_size, input_seq_length-1]
    #   eval_data[0].trg_y -> tensor (= eval_data[0].src), shape [batch_size, input_seq_length-1]
    eval_data = list(data_gen(num_words=num_words, batch_size=batch_size, num_batches=100, length=input_seq_length, pad_index=PAD_TOKEN, sos_index=SOS_TOKEN))

    # record the perplexities on eval_data
    dev_perplexities = []

    if USE_CUDA:
        model.cuda()

    for epoch in range(epochs):
        print("Epoch %d" % epoch)

        ######################## train ########################
        # set the model to train mode
        model.train()
        # data used for training, length of 100, each item is a Batch object
        data = data_gen(num_words=num_words, batch_size=batch_size, num_batches=100)
        # train the model
        run_epoch(data, model, SimpleLossCompute(model.generator, criterion, optim))

        ###################### evaluate #######################
        # set the model to evaluate mode, weights won't change
        model.eval()
        with torch.no_grad():

            perplexity = run_epoch(eval_data, model, SimpleLossCompute(model.generator, criterion, None))
            print("Evaluation perplexity: %f" % perplexity)
            dev_perplexities.append(perplexity)
            print_examples(eval_data, model, n=2, max_len=9)

    return dev_perplexities


def plot_perplexity(perplexities):
    """plot perplexities"""
    plt.title("Perplexity per Epoch")
    plt.xlabel("Epoch")
    plt.ylabel("Perplexity")
    plt.plot(perplexities)
    plt.show()

