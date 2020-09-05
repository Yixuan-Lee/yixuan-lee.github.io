#include <utility>

#ifndef LINKEDLISTBST_H
#define LINKEDLISTBST_H

#include <algorithm>    // max
#include <iostream>
#include <stdexcept>
#include <set>

using std::cout;
using std::endl;
using std::set;

template<typename T>
class LinkedTreeNodesBST {
private:
    // Tree Node
    struct TreeNode {
        T data;
        int id;     // same as index in ArrayBST
        TreeNode *leftChild;
        TreeNode *rightChild;

        // constructor
        explicit TreeNode(T data, int id = 1, TreeNode *left = nullptr, TreeNode *right = nullptr)
            : id {id}, data {data}, leftChild {left}, rightChild {right} {
        }
    };

public:
    // default constructor
    LinkedTreeNodesBST();

    // constructor
    explicit LinkedTreeNodesBST(T value);

    // compare two BSTs
    bool operator==(const LinkedTreeNodesBST<T> &);

    /////////////////////////// Big Five  ////////////////////////////
    // 1. destructor
    virtual ~LinkedTreeNodesBST();

    // 2. copy constructor
    LinkedTreeNodesBST(const LinkedTreeNodesBST &);

    // 3. copy assignment operator
    LinkedTreeNodesBST& operator=(const LinkedTreeNodesBST &);

    // 4. move constructor
    LinkedTreeNodesBST(LinkedTreeNodesBST &&) noexcept;

    // 5. move assignment operator
    LinkedTreeNodesBST& operator=(LinkedTreeNodesBST &&) noexcept;

    //////////////////////////////////////////////////////////////////

    ////////////////////// Principle Operations //////////////////////
    TreeNode* insertRecursive(TreeNode *root, int id, T value);

    void insertIterative(TreeNode *root, T value);

    TreeNode* remove(TreeNode *root, T value);

    TreeNode* searchByValueRecursive(TreeNode* root, T value);

    TreeNode* searchByValueIterative(TreeNode* root, T value);

    void preOrder(const TreeNode *root) const;

    void inOrder(const TreeNode *root) const;

    void postOrder(const TreeNode *root) const;

    void levelOrder(const TreeNode *root) const;

    size_t getHeight() const;

    TreeNode* getRoot() const;
    //////////////////////////////////////////////////////////////////

    ////////////////////// Auxiliary Operations //////////////////////
    bool isEmpty() const;

    bool isBST(const TreeNode *root, T minValue, T maxValue) const;

//    TreeNode& getParent(const TreeNode &node) const;

//    TreeNode& getLeftChild(const TreeNode &node) const;

//    TreeNode& getRightChild(const TreeNode &node) const;

    size_t countNodes() const;

    void visualizeBST();

    T minValue();

    T maxValue();
    //////////////////////////////////////////////////////////////////


private:
    TreeNode *root;

    size_t count;

    /////////////////////// Auxiliary Function ///////////////////////
    bool isEqual(const TreeNode *, const TreeNode *);

    void deepcopy(TreeNode *, const TreeNode *);

    void destroyTree(TreeNode *root);

    TreeNode* findMinimumNode(TreeNode *root);

    bool printLevel(const TreeNode *root, int level) const;

    size_t calcHeight(const TreeNode *root) const;

    //////////////////////////////////////////////////////////////////
};

/////////////////////// Function Implementation ///////////////////////
// default constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST() : root{nullptr}, count{0} {
}

// constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST(T value) {
    root = new TreeNode(value);
    count = 1;
}

// compare two BSTs
template<typename T>
bool LinkedTreeNodesBST<T>::operator==(const LinkedTreeNodesBST<T> &llb) {
    return isEqual(this->root, llb.root);
}

///////////////////////////// Big Five /////////////////////////////
// 1. destructor
template<typename T>
LinkedTreeNodesBST<T>::~LinkedTreeNodesBST() {
    destroyTree(root);
    count = 0;
}

// 2. copy constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST(const LinkedTreeNodesBST &llb) {
    if (!isEmpty()) {
        // destroy the current BST
        destroyTree(root);
    }
    // copy the root node and count
    root = new TreeNode(llb.root->data);
    count = llb.count;
    // deepcopy llb's left and right subtrees
    deepcopy(root, llb.root);
}

// 3. copy assignment operator=
template<typename T>
LinkedTreeNodesBST<T>& LinkedTreeNodesBST<T>::operator=(const LinkedTreeNodesBST &llb) {
    // check self-assignment
    if (this == &llb) {
        return *this;
    }

    if (!isEmpty()) {
        // destroy the current BST
        destroyTree(root);
    }
    // copy the root node and count
    root = TreeNode(llb.root->data);
    count = llb.count;
    // deepcopy llb's left and right subtrees
    deepcopy(root, llb.root);

    return *this;
}

// 4. move constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST(LinkedTreeNodesBST &&llb) noexcept {
    if (llb == nullptr) {
        return;
    }
    // steal everything from llb
    // for simplicity, just make root point to llb.root
    root = llb.root;
    count = llb.count;

    // reset llb to stable states
    llb.root = nullptr;
}

// 5. move assignment operator=
template<typename T>
LinkedTreeNodesBST<T>& LinkedTreeNodesBST<T>::operator=(LinkedTreeNodesBST &&llb) noexcept {
    // check self-assignment
    if (this == &llb) {
        return *this;
    }

    if (!isEmpty()) {
        // destroy the current BST
        destroyTree(root);
    }
    // steal everything from llb
    // for simplicity, just make root point to llb.root
    root = llb.root;

    // reset llb to stable states
    llb.root = nullptr;

    return *this;
}

/////////////////////// Principle Operations ///////////////////////
// insert (recursive approach)
template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::insertRecursive(TreeNode *root, int id, T value) {
    if (root == nullptr) {
        count++;
        return new TreeNode(value, id);
    } else if (root->data == value) {
        // we assume all values in BST are unique
        // so refuse to insert
        throw std::runtime_error("duplicate value is inserted.");
    } else if (root->data > value) {
        // insert the value in the left subtree
        root->leftChild = insertRecursive(root->leftChild, root->id * 2, value);
    } else {
        // insert the value in the right subtree
        root->rightChild = insertRecursive(root->rightChild, root->id * 2 + 1, value);
    }
    return root;
}

// insert (iterative approach)
template<typename T>
void LinkedTreeNodesBST<T>::insertIterative(TreeNode *root, T value) {
    // start with root node
    TreeNode *curr = root;
    // store parent node of current node
    TreeNode *parent = nullptr;

    // if current BST is empty
    if (curr == nullptr) {
        curr = new TreeNode(value);
    }

    // traverse the tree and find the right parent node
    while (curr != nullptr) {
        // update parent node as current node
        parent = curr;

        if (value < curr->data) {
            // traverse current's left subtree if value < curr->value
            curr = curr->leftChild;
        } else {
            // traverse current's right subtree if value > curr->value
            curr = curr->rightChild;
        }
    }
    // so far, we have found the right parent node whose the new value belongs

    // create a new TreeNode and assign it to appropriate left/right pointer
    if (value < parent->data) {
        parent->leftChild = new TreeNode(value, parent->id * 2);
        count++;
    } else {
        parent->rightChild = new TreeNode(value, parent->id * 2 + 1);
        count++;
    }
}

// remove node with certain value
template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::remove(LinkedTreeNodesBST<T>::TreeNode *root, T value) {
    if (root == nullptr) {
        // BST is empty
        return nullptr;
    }
    if (value < root->data) {
        // value should be in the root's left subtree
        // update leftChild pointer as the returned TreeNode
        root->leftChild = remove(root->leftChild, value);
    } else if (value > root->data) {
        // value should be in the root's right subtree
        // update rightChild pointer as the returned TreeNode
        root->rightChild = remove(root->rightChild, value);
    } else {
        // the node to be removed is found

        if (root->leftChild == nullptr && root->rightChild == nullptr) {
            // scenario 1: leaf node, the node has no children
            delete root;    // wipe out the memory
            root = nullptr;
            count--;
        } else if (root->leftChild != nullptr && root->rightChild == nullptr) {
            // scenario 2.1: partial internal node with a left child
            TreeNode* temp = root;
            root = root->leftChild; // make the current pointer point to the left child
            delete temp;    // wipe out the memory
            temp = nullptr;
            count--;
        } else if (root->leftChild == nullptr && root->rightChild != nullptr) {
            // scenario 2.2: partial internal node with a right child
            TreeNode *temp = root;
            root = root->rightChild;
            delete temp;
            temp = nullptr;
            count--;
        } else {
            // scenario 3: complete internal node with two children
            // step 1: find the minimum node in the right subtree
            TreeNode* minimum = findMinimumNode(root->rightChild);
            if (minimum != nullptr) {
                // step 2: replace the value of current node with the minimum value
                root->data = minimum->data;
                // step 3: remove the minimum node
                root->rightChild = remove(root->rightChild, minimum->data);
            } else {
                // program won't go to here, since scenario 3 illustrates root is a complate internal node
                // so root->rightChild is not empty, there has to be a non-nullptr TreeNode* returned.
            }
        }
    }
    return root;
}

// search TreeNode by value (recursive approach)
template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::searchByValueRecursive(TreeNode* root, T value) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->data == value) {
        return root;
    } else if (root->data > value) {
        // search in the left subtree
        return searchByValueRecursive(root->leftChild, value);
    } else {
        // search in the right subtree
        return searchByValueRecursive(root->rightChild, value);
    }
}

// search TreeNode by value (iterative approach)
template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::searchByValueIterative(TreeNode* root, T value) {
    // keep reference to the current root
    TreeNode* curr = root;
    // traverse root's appropriate subtree
    while (curr != nullptr) {
        if (curr->data == value) {
            return curr;
        } else if (curr->data > value) {
            // go to left subtree
            curr = curr->leftChild;
        } else {
            // go to right subtree
            curr = curr->rightChild;
        }
    }
    return curr;
}

// four types of tree traversal: preOrder, inOrder, postOrder, levelOrder
template<typename T>
void LinkedTreeNodesBST<T>::preOrder(const LinkedTreeNodesBST<T>::TreeNode *root) const {
    if (root == nullptr) {
//        cout << "(_)";
        return;
    }

    // visit and print the current node
    cout << root->data << " ";
//    cout << "(";

    // visit left child
    preOrder(root->leftChild);

    // visit right child
    preOrder(root->rightChild);

//    cout << ")";
}

template<typename T>
void LinkedTreeNodesBST<T>::inOrder(const LinkedTreeNodesBST<T>::TreeNode *root) const {
    if (root == nullptr) {
//        cout << "(_)";
        return;
    }

//    cout << "(";

    // visit left child first
    inOrder(root->leftChild);

    // visit and print the current node
//    cout << ")";
    cout << root->data << " ";
//    cout << "(";

    // visit right child
    inOrder(root->rightChild);

//    cout << ")";
}

template<typename T>
void LinkedTreeNodesBST<T>::postOrder(const LinkedTreeNodesBST<T>::TreeNode *root) const {
    if (root == nullptr) {
//        cout << "(_)";
        return;
    }

    // visit left child
//    cout << "(";

    postOrder(root->leftChild);

//    cout << ")(";

    // visit right child
    postOrder(root->rightChild);

//    cout << ")";

    // visit and print the current node
    cout << root->data << " ";
}

template<typename T>
void LinkedTreeNodesBST<T>::levelOrder(const LinkedTreeNodesBST<T>::TreeNode *root) const {
    if (root == nullptr) {
        // empty tree
        return;
    }

    // start from level 1
    int level = 1;
    while (printLevel(root, level)) {
        level++;
    }
}

// there are two approaches to find the height
// approach 1: recursive calculate the height of left subtree and right subtree and select the max
// approach 2: since the program records the id for each TreeNode, we can find the rightmost TreeNode at the deepest level, and calculate the height based on its id and the formula
// the getHeight uses approach 1
template<typename T>
size_t LinkedTreeNodesBST<T>::getHeight() const {
    return calcHeight(root);
}

template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::getRoot() const {
    return root;
}

/////////////////////// Auxiliary Operations ///////////////////////
template<typename T>
bool LinkedTreeNodesBST<T>::isEmpty() const {
    return root == nullptr;
}

template<typename T>
bool LinkedTreeNodesBST<T>::isBST(const LinkedTreeNodesBST<T>::TreeNode *root, T minValue, T maxValue) const {
    if (root == nullptr) {
        return true;
    }
    if (root->data < minValue || root->data > maxValue) {
        return false;
    }
    return isBST(root->leftChild, minValue, root->data - 1)
        && isBST(root->rightChild, root->data + 1, maxValue);
}

template<typename T>
size_t LinkedTreeNodesBST<T>::countNodes() const {
    return count;
}

// iterative approach or recursive approach can both be applied
// here iterative approach is used
template<typename T>
T LinkedTreeNodesBST<T>::minValue() {
    if (isEmpty()) {
        throw std::runtime_error("BST is empty.");
    }
    TreeNode *curr = root;
    while (curr->leftChild != nullptr) {
        curr = curr->leftChild;
    }
    return curr->data;
}

// iterative approach or recursive approach can both be applied
// here iterative approach is used
template<typename T>
T LinkedTreeNodesBST<T>::maxValue() {
    if (isEmpty()) {
        throw std::runtime_error("BST is empty.");
    }
    TreeNode *curr = root;
    while (curr->rightChild != nullptr) {
        curr = curr->rightChild;
    }
    return curr->data;
}

/////////////////////// Auxiliary Functions ////////////////////////
template<typename T>
bool LinkedTreeNodesBST<T>::isEqual(const LinkedTreeNodesBST<T>::TreeNode *root1,
        const LinkedTreeNodesBST<T>::TreeNode *root2) {
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    if (root1 != nullptr && root2 != nullptr
        && isEqual(root1->leftChild, root2->leftChild)
        && isEqual(root1->rightChild, root2->rightChild)) {
        // so far, the structures of root1 and root2 are same
        // next, check the node values
        return root1->data == root2->data;
    }
    return false;
}

template<typename T>
void LinkedTreeNodesBST<T>::deepcopy(LinkedTreeNodesBST<T>::TreeNode *destRoot,
        const LinkedTreeNodesBST<T>::TreeNode *srcRoot) {
    if (srcRoot == nullptr) {
        // return when reaching to leaf node
        return;
    }
    if (destRoot == nullptr) {
        // create a TreeNode with the value of srcRoot
        destRoot = new TreeNode(srcRoot->data);
    }
    if (srcRoot->leftChild != nullptr) {
        // create a TreeNode with the value of srcRoot's left child
        destRoot->leftChild = new TreeNode(srcRoot->leftChild->data);
        // deepcopy srcRoot's left subtree
        deepcopy(destRoot->leftChild, srcRoot->leftChild);
    }
    if (srcRoot->rightChild != nullptr) {
        // create a TreeNode with the value of srcRoot's right child
        destRoot->rightChild = new TreeNode(srcRoot->rightChild->data);
        // deepcopy srcRoot's right subtree
        deepcopy(destRoot->rightChild, srcRoot->rightChild);
    }
}

template<typename T>
void LinkedTreeNodesBST<T>::destroyTree(TreeNode *root) {
    if (root != nullptr) {
        // delete its left and right subtrees
        destroyTree(root->leftChild);
        destroyTree(root->rightChild);
        // and then delete itself
        delete root;
        // defensive programming
        root = nullptr;
    }
}

template<typename T>
typename LinkedTreeNodesBST<T>::TreeNode* LinkedTreeNodesBST<T>::findMinimumNode(LinkedTreeNodesBST<T>::TreeNode *root) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->leftChild != nullptr) {
        // the most left node is the minimum node
        return findMinimumNode(root->leftChild);
    } else {
        return root;
    }
}

template<typename T>
bool LinkedTreeNodesBST<T>::printLevel(const LinkedTreeNodesBST<T>::TreeNode *root, int level) const {
    if (root == nullptr) {
        // reach to the end
        return false;
    }
    if (level == 1) {
        cout << root->data << " ";
        return true;
    }
    bool left = printLevel(root->leftChild, level - 1);
    bool right = printLevel(root->rightChild, level - 1);
    return left || right;
}

template<typename T>
size_t LinkedTreeNodesBST<T>::calcHeight(const LinkedTreeNodesBST<T>::TreeNode *root) const {
    if (root == nullptr) {
        // reach to the end
        return 0;
    } else {
        size_t leftSubtreeHeight = calcHeight(root->leftChild);
        size_t rightSubtreeHeight = calcHeight(root->rightChild);
        return std::max(leftSubtreeHeight, rightSubtreeHeight) + 1;
    }
}

template<typename T>
void LinkedTreeNodesBST<T>::visualizeBST() {
    // create a dummy class containing 4 functions for tree visualization
    class dummy {
    public:
        dummy(set<int> s) : S{std::move(s)} {
        }

        void indent(int level) {
            for (int i = 0; i < level; ++i) {
                if (S.count(i) == 1) {
                    cout << "| ";
                } else {
                    cout << " ";
                }
            }
        }

        // tee shape starts a vertical bar
        void tee(int level) {
            indent(level);
            cout << "|-";
            S.insert(level);
        }

        // ell shape ends one in the same column
        void ell(int level) {
            indent(level);
            cout << "`-";
            S.erase(level);
        }

        void print(TreeNode *node, int level) {
            if (node == nullptr) {
                // only print when node only has 1 child
                cout << "[null]" << endl;
            } else {
                // print node
                cout << "(" << node->data << ")" << endl;
                // recursively print node's children
                tee(level);
                print(node->leftChild, level + 1);
                ell(level);
                print(node->rightChild, level + 1);
            }
        }

    private:
        // S tracks which columns need the vertical bars
        set<int> S;
    };

    dummy treeVisulizer(std::set<int>{});
    treeVisulizer.print(getRoot(), 1);
}

#endif //LINKEDLISTBST_H
