#ifndef ARRAYBST_H
#define ARRAYBST_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>

using std::set;
using std::cout;
using std::endl;

/**
 *
 * @tparam T          generic type, expected to overload operator=, operator<
 * @tparam SIZE
 * @tparam initValue
 */
template<typename T, T initValue, size_t SIZE = 1> // index 0 is not used
class ArrayBST {
public:
    // default constructor
    ArrayBST();

    // constructor
    explicit ArrayBST(T rootValue);

    // compare two BSTs
    bool operator==(const ArrayBST &abst);

    /////////////////////////// Big Five  ////////////////////////////
    // 1. destructor
    virtual ~ArrayBST();

    // 2. copy constructor
    ArrayBST(const ArrayBST &abst);

    // 3. copy assignment operator=
    ArrayBST& operator=(const ArrayBST &abst);

    // 4. move constructor
    ArrayBST(ArrayBST &&abst) noexcept;

    // 5. move assignment operator=
    ArrayBST& operator=(ArrayBST &&abst) noexcept;

    //////////////////////////////////////////////////////////////////

    ////////////////////// Principle Operations //////////////////////
    void insert(T value);

    T remove(size_t index, T value);

    T searchByValue(T value);

    void preOrder(size_t index);

    void inOrder(size_t index);

    void postOrder(size_t index);

    void levelOrder(size_t index);

    int getHeight();

    T getRootValue();

    //////////////////////////////////////////////////////////////////

    ////////////////////// Auxiliary Operations //////////////////////
    bool isEmpty() const;

    size_t countNodes() const;

    void visualizeBST();

    T minValue();

    T maxValue();

    //////////////////////////////////////////////////////////////////

private:
    T* bst;

    size_t count;

    size_t capacity;

    T initVal;

    const size_t rootId = 1;

    /////////////////////// Auxiliary Function ///////////////////////
    void destroyTree();

    void doublesize();

    void reorganizeSubtree(size_t subtreeRootIndex, size_t subtreeRootIndexMoveTo = -1);

    size_t findMinimumIndex(size_t currentIndex);

};

/////////////////////// Function Implementation ///////////////////////
// default constructor
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>::ArrayBST() : bst {new T[SIZE]}, count{0}, capacity {SIZE}, initVal {initValue} {
    std::fill_n(bst, capacity, initValue);
}

// constructor
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>::ArrayBST(T rootValue) {
    // keep references
    count = 1;
    capacity = SIZE;
    initVal = initValue;
    // fill bst with initVal values
    bst = new T[SIZE + 1];
    std::fill_n(bst, capacity + 1, initValue);
    // set root value
    bst[rootId] = rootValue;
}

// compare two BSTs
template<typename T, T initValue, size_t SIZE>
bool ArrayBST<T, initValue, SIZE>::operator==(const ArrayBST &abst) {
    if (count != abst.count) {
        return false;
    }
    for (int i = 1; i <= std::min(capacity, abst.capacity); ++i) {
        if (bst[i] != initVal && abst.bst[i] != abst.initVal && bst[i] != abst.bst[i]) {
            return false;
        }
    }
    // check if one of the trees has more un-null nodes
    // if all actual nodes have the same data, then consider two BSTs are same
    // although one may has bigger capacity
    for (int i = std::min(capacity, abst.capacity) + 1; i <= std::max(capacity, abst.capacity); ++i) {
        if (i <= capacity && bst[i] != initVal) {
            return false;
        }
        if (i <= abst.capacity && abst.bst[i] != abst.initVal) {
            return false;
        }
    }
    return true;
}

//////////////////////////// Big Five  /////////////////////////////
// 1. destructor
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>::~ArrayBST() {
    destroyTree();
}

// 2. copy constructor
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>::ArrayBST(const ArrayBST &abst) {
    if (!isEmpty()) {
        // destroy the current BST
        destroyTree();
    }
    // allocation
    bst = new T[abst.capacity + 1];
    // copy element-wisely
    for (int i = 0; i <= abst.capacity; ++i) {
        // shallow copy or deep copy depends on the implementation of operator= overload in T
        bst[i] = abst[i];
    }
    count = abst.count;
    capacity = abst.capacity;
}

// 3. copy assignment operator=
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>& ArrayBST<T, initValue, SIZE>::operator=(const ArrayBST &abst) {
    // check self-assignment
    if (this == &abst) {
        return *this;
    }
    if (!isEmpty()) {
        // destroy the current BST
        destroyTree();
    }
    // allocation
    bst = new T[abst.capacity + 1];
    // copy element-wisely
    for (int i = 0; i <= abst.capacity; ++i) {
        // shallow copy or deep copy depends on the implementation of operator= overload in T
        bst[i] = abst[i];
    }
    count = abst.count;
    capacity = abst.capacity;

    return *this;
}

// 4. move constructor
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>::ArrayBST(ArrayBST &&abst) noexcept {
    if (abst.isEmpty()) {
        return;
    }
    // steal everything from abst to initialzie *this
    // for simplicity, just make bst pointer point to abst.bst and redirect abst.bst to nullptr
    bst = abst.bst;
    count = abst.count;
    capacity = abst.capacity;

    // reset abst to stable states
    abst.bst = nullptr;
    abst.count = 0;
    abst.capacity = 0;
}

// 5. move assignment operator=
template<typename T, T initValue, size_t SIZE>
ArrayBST<T, initValue, SIZE>& ArrayBST<T, initValue, SIZE>::operator=(ArrayBST &&abst) noexcept {
    // check self-assignment
    if (this == &abst) {
        return *this;
    }
    if (!isEmpty()) {
        // destroy the current BST
        destroyTree();
    }
    // steal everything from abst to initialzie *this
    // for simplicity, just make bst pointer point to abst.bst and redirect abst.bst to nullptr
    bst = abst.bst;
    count = abst.count;
    capacity = abst.capacity;

    // reset abst to stable states
    abst.bst = nullptr;
    abst.count = 0;
    abst.capacity = 0;

    return *this;
}


/////////////////////// Principle Operations ///////////////////////
template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::insert(T value) {
    size_t currId = rootId;
    if (bst[currId] == initValue) {
        // current BST is empty
        bst[currId] = value;
    }

    while (bst[currId] != initValue) {
        if (value < bst[currId]) {
            // value should be inserted in the left subtree
            currId = currId * 2;
        } else {
            // value should be inserted in the right subtree
            currId = currId * 2 + 1;
        }
        if (currId > capacity) {
            // double the capacity
            doublesize();
        }
    }
    // so far, we have found the correct index to insert

    // assign the value
    bst[currId] = value;
    count++;
}

template<typename T, T initValue, size_t SIZE>
T ArrayBST<T, initValue, SIZE>::remove(size_t index, T value) {
    if (isEmpty()) {
        throw std::runtime_error("BST is empty, invalid remove.");
    }
    // search for the node with value in the BST
    size_t curr = rootId;
    while (curr <= capacity && bst[curr] != value && bst[curr] != initValue) {
        if (value < bst[curr]) {
            // search in the left subtree
            curr = 2 * curr;
        } else {
            // search in the right subtree
            curr = 2 * curr + 1;
        }
    }
    // so far, we should either find the appropriate index or bst[curr] = initValue or curr > capacity

    if (curr > capacity || bst[curr] == initValue) {
        // if node with the value is not found
        throw std::runtime_error("value is not found in BST.");
    } else {
        T ret = -1;
        size_t leftChildIdx = curr * 2;
        size_t rightChildIdx = curr * 2 + 1;
        if (leftChildIdx < capacity && rightChildIdx < capacity) {
            if (bst[leftChildIdx] == initValue && bst[rightChildIdx] == initValue) {
                // scenario 1: leaf node, the node has no children
                ret = bst[curr];
                bst[curr] = initValue;  // reset current to initial value
                count--;
            } else if (bst[leftChildIdx] != initValue && bst[rightChildIdx] == initValue) {
                // scenario 2.1: partial internal node with a left child
                // replace current value with the value of left child
                ret = bst[curr];
                bst[curr] = bst[leftChildIdx];
                // update left subtree recursively
                reorganizeSubtree(leftChildIdx, curr);
                count--;
            } else if (bst[leftChildIdx] == initValue && bst[rightChildIdx] != initValue) {
                // scenario 2.2: partial internal node with a right child
                // replace current value with the value of right child
                ret = bst[curr];
                bst[curr] = bst[rightChildIdx];
                // update right subtree recursively
                reorganizeSubtree(rightChildIdx, curr);
                count--;
            } else if (bst[leftChildIdx] != initValue && bst[rightChildIdx] != initValue) {
                // scenario 3: complete internal node with two children
                // step 1: find the index of minimum node in the right subtree
                size_t minimumNodeIndex = findMinimumIndex(rightChildIdx);
                // step 2: replace the value of current node with the minimum value
                ret = bst[curr];
                bst[curr] = bst[minimumNodeIndex];
                // step 3: remove the minimum node
                // because minimumNode should be the leftmost node in the right subtree
                // it shouldn't have a left child, so only reorganizing its right subtree is necessary
                // if the right subtree exists
                bst[minimumNodeIndex] = initValue;
                if (2 * minimumNodeIndex + 1 <= capacity && bst[2 * minimumNodeIndex + 1] != initValue) {
                    // move right value to the minimumIndex which is moved to root
                    bst[minimumNodeIndex] = bst[2 * minimumNodeIndex + 1];
                    // set right value to initVal
                    bst[2 * minimumNodeIndex + 1] = initVal;
                    // reorganize the right subtree
                    reorganizeSubtree(2 * minimumNodeIndex + 1, minimumNodeIndex);
                }
                count--;
            }
        } else {
            // scenario 1: leaf node, the node has no children
            ret = bst[curr];
            bst[curr] = initValue;
            count--;
        }
        return ret;
    }
}

template<typename T, T initValue, size_t SIZE>
T ArrayBST<T, initValue, SIZE>::searchByValue(T value) {
    // keep reference to current index
    size_t curr = rootId;
    // traverse root's appropriate subtree
    while (curr <= capacity && bst[curr] != initValue) {
        if (bst[curr] == value) {
            return bst[curr];
        } else if (bst[curr] > value) {
            // go to left subtree
            curr = curr * 2;
        } else {
            // go to right subtree
            curr = curr * 2 + 1;
        }
    }
    return -1;
}

// four types of tree traversal: preOrder, inOrder, postOrder, levelOrder
template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::preOrder(size_t index) {
    if (index > capacity || bst[index] == initValue) {
        return;
    }

    // visit and print the current node
    cout << bst[index] << " ";

    // visit left child
    preOrder(index * 2);

    // visit right child
    preOrder(index * 2 + 1);
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::inOrder(size_t index) {
    if (index > capacity || bst[index] == initValue) {
        return;
    }

    // visit left child first
    inOrder(index * 2);

    // visit and print the current node
    cout << bst[index] << " ";

    // visit right child
    inOrder(index * 2 + 1);
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::postOrder(size_t index) {
    if (index > capacity || bst[index] == initValue) {
        return;
    }

    // visit left child
    postOrder(index * 2);

    // visit right child
    postOrder(index * 2 + 1);

    // visit and print the current node
    cout << bst[index] << " ";
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::levelOrder(size_t index) {
    if (index > capacity || bst[index] == initValue) {
        return;
    }

    for (size_t level = 1; level <= getHeight(); ++level) {
        for (size_t i = std::pow(2, level - 1); i < std::pow(2, level); ++i) {
            cout << bst[i] << " ";
        }
    }
}

template<typename T, T initValue, size_t SIZE>
int ArrayBST<T, initValue, SIZE>::getHeight() {
    if (isEmpty()) {
        return 0;
    }
    // find the maximum index with non-initValue
    int maximumIndex = 1;
    for (int i = static_cast<int>(capacity); i >= 1; --i) {
        if (bst[i] != initValue)  {
            maximumIndex = i;
            break;
        }
    }
    return static_cast<int>(std::floor(std::log2(maximumIndex)) + 1);
}

template<typename T, T initValue, size_t SIZE>
T ArrayBST<T, initValue, SIZE>::getRootValue() {
    if (isEmpty()) {
        throw std::runtime_error("current BST is empty.");
    }
    return bst[rootId];
}


/////////////////////// Auxiliary Functions ////////////////////////
template<typename T, T initValue, size_t SIZE>
bool ArrayBST<T, initValue, SIZE>::isEmpty() const {
    return count == 0;
}

template<typename T, T initValue, size_t SIZE>
size_t ArrayBST<T, initValue, SIZE>::countNodes() const {
    return count;
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::visualizeBST() {
    // create a dummy class containing 4 functions for tree visualization
    class dummy {
    public:
        dummy(set<int> s, ArrayBST &abst) : S{std::move(s)}, tree{abst} {
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

        void print(size_t index, int level) {
            if (index > tree.capacity || tree.bst[index] == initValue) {
                // only print when node only has 1 child
                cout << "[null]" << endl;
            } else {
                // print node
                cout << "(" << tree.bst[index] << ")" << endl;
                // recursively print node's children
                tee(level);
                print(index * 2, level + 1);
                ell(level);
                print(index * 2 + 1, level + 1);
            }
        }

    private:
        // S tracks which columns need the vertical bars
        set<int> S;

        const ArrayBST& tree;
    };

    dummy treeVisulizer(std::set<int>{}, *this);
    treeVisulizer.print(rootId, 1);
}

template<typename T, T initValue, size_t SIZE>
T ArrayBST<T, initValue, SIZE>::minValue() {
    if (isEmpty()) {
        throw std::runtime_error("BST is empty.");
    }
    size_t curr = rootId;
    while (curr * 2 <= capacity && bst[curr * 2] != initValue) {
        // go to left child
        curr = curr * 2;
    }
    return bst[curr];
}

template<typename T, T initValue, size_t SIZE>
T ArrayBST<T, initValue, SIZE>::maxValue() {
    if (isEmpty()) {
        throw std::runtime_error("BST is empty.");
    }
    size_t curr = rootId;
    while (curr * 2 + 1 <= capacity && bst[curr * 2 + 1] != initValue) {
        // go to right child
        curr = curr * 2 + 1;
    }
    return bst[curr];
}

/////////////////////// Auxiliary Function ///////////////////////
template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::destroyTree() {
    delete[] bst;
    bst = nullptr;
    count = 0;
    capacity = 0;
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::doublesize() {
    size_t doubleCapacity = 2 * capacity;

    // allocate new array
    T *temp = this->bst;
    this->bst = new T[doubleCapacity + 1];
    std::fill_n(this->bst, doubleCapacity + 1, initValue);

    // element-wise copy
    for (size_t i = 0; i <= capacity; ++i) {
        // whether shallow copy or deep copy depends on behavior on overloaded operator= in T
        if (temp[i] != initValue) {
            this->bst[i] = temp[i];
        }
    }
    capacity = doubleCapacity;

    // de-allocation
    delete[] temp;
}

template<typename T, T initValue, size_t SIZE>
void ArrayBST<T, initValue, SIZE>::reorganizeSubtree(size_t subtreeRootIndex, size_t subtreeRootIndexMoveTo) {
    if (subtreeRootIndex > capacity) {
        return;
    }
    bst[subtreeRootIndex] = initVal;
    size_t leftChildIndex = 2 * subtreeRootIndex;
    size_t rightChildIndex = 2 * subtreeRootIndex + 1;

    // update left subtree
    if (leftChildIndex <= capacity && bst[leftChildIndex] != initVal) {
        bst[subtreeRootIndexMoveTo * 2] = bst[leftChildIndex];
        // set current to initValue
        bst[leftChildIndex] = initValue;
        // update left subtree recursively
        reorganizeSubtree(leftChildIndex, subtreeRootIndexMoveTo * 2);
    }
    // update right subtree
    if (rightChildIndex <= capacity && bst[rightChildIndex] != initVal) {
        bst[subtreeRootIndexMoveTo * 2 + 1] = bst[rightChildIndex];
        // set current to initValue
        bst[rightChildIndex] = initValue;
        // update right subtree recursively
        reorganizeSubtree(rightChildIndex, subtreeRootIndexMoveTo * 2 + 1);
    }
}

template<typename T, T initValue, size_t SIZE>
size_t ArrayBST<T, initValue, SIZE>::findMinimumIndex(size_t currentIndex) {
    size_t leftChildIndex = 2 * currentIndex;
    if (leftChildIndex > capacity || bst[leftChildIndex] == initValue) {
        return currentIndex;
    } else {
        return findMinimumIndex(leftChildIndex);
    }
}

#endif //ARRAYBST_H
