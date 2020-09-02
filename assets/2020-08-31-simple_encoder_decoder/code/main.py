# import libraries
import torch
from helper import train_copy_task
from helper import plot_perplexity

# use CUDA if it is available
USE_CUDA = torch.cuda.is_available()
DEVICE=torch.device('cuda:0') # or set to 'cpu'
print("CUDA:", USE_CUDA)
print(DEVICE)


#############################################################################

# train the copy task
dev_perplexities = train_copy_task()

plot_perplexity(dev_perplexities)
