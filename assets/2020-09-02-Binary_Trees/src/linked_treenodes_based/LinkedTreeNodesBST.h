#ifndef LINKEDLISTBST_H
#define LINKEDLISTBST_H

#include <iostream>

template<typename T>
class LinkedTreeNodesBST {
private:
    // Tree Node
    struct TreeNode {
        T data;
        TreeNode *leftChild;
        TreeNode *rightChild;

        // constructor
        TreeNode(T data, TreeNode *left = nullptr, TreeNode *right = nullptr) : data {data}, leftChild {left}, rightChild {right} {
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
    void insert(T value);

    T remove(T value);

    TreeNode& searchByValue(T value);

    void preOrder(const TreeNode &) const;

    void inOrder(const TreeNode &) const;

    void postOrder(const TreeNode &) const;

    void levelOrder(const TreeNode &) const;

    size_t getHeight() const;

    TreeNode& getRoot() const;
    //////////////////////////////////////////////////////////////////

    ////////////////////// Auxiliary Operations //////////////////////
    bool isEmpty() const;

    bool isBST(const TreeNode &) const;

    TreeNode& getParent(const TreeNode &) const;

    TreeNode& getLeftChild(const TreeNode &) const;

    TreeNode& getRightChild(const TreeNode &) const;

    size_t countNodes() const;

    void destroyTree(TreeNode *);

    //////////////////////////////////////////////////////////////////


private:
    TreeNode *root;

    /////////////////////// Auxiliary Function ///////////////////////
    bool isEqual(const TreeNode *, const TreeNode *);

    void deepcopy(TreeNode *, const TreeNode *);

    //////////////////////////////////////////////////////////////////
};

/////////////////////// Function Implementation ///////////////////////
// default constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST() : root{nullptr} {
}

// constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST(T value) {
    if (root != nullptr) {
        destroyTree();
    }
    root = new TreeNode(value);
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
}

// 2. copy constructor
template<typename T>
LinkedTreeNodesBST<T>::LinkedTreeNodesBST(const LinkedTreeNodesBST &llb) {
    if (!isEmpty()) {
        // destroy the current BST
        destroyTree(root);
    }
    // copy the root node
    root = new TreeNode(llb.root->data);
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
    // copy the root node
    root = TreeNode(llb.root->data);
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
template<typename T>
void LinkedTreeNodesBST<T>::insert(T value) {
    // TODO: continue
}


/////////////////////// Auxiliary Operations ///////////////////////
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
        return true;
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

#endif //LINKEDLISTBST_H
