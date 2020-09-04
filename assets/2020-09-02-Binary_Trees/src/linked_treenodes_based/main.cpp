#include <iostream>
#include <assert.h>
#include "LinkedTreeNodesBST.h"

using std::cout;
using std::endl;

const int rootId = 1;

int main() {
    // test default constructor
    LinkedTreeNodesBST<int> ltnb_1;
    assert(ltnb_1.countNodes() == 0);
    assert(ltnb_1.isEmpty() == true);

    // test constructor
    LinkedTreeNodesBST<int> ltnb_2(20);
    assert(ltnb_2.countNodes() == 1);
    assert(ltnb_2.isEmpty() == false);
    ltnb_2.visualizeBST();
    cout << "=============================================================\n";

    // test insertRecursive, insertIterative, visualizeBST
    // insert nodes in the left subtree
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 10);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 5);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 15);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 1);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 9);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 7);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 6);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 8);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 11);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 18);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 16);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 17);
    ltnb_2.insertRecursive(ltnb_2.getRoot(), rootId, 19);
    // insert nodes in the right subtree
    ltnb_2.insertIterative(ltnb_2.getRoot(), 30);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 25);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 35);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 21);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 29);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 26);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 27);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 28);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 31);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 39);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 38);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 41);
    ltnb_2.insertIterative(ltnb_2.getRoot(), 40);
    ltnb_2.visualizeBST();
    cout << "=============================================================\n";

    LinkedTreeNodesBST<int> ltnb_3(6);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 3);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 1);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 0);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 2);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 4);
    ltnb_3.insertRecursive(ltnb_3.getRoot(), rootId, 5);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 9);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 8);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 7);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 11);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 10);
    ltnb_3.insertIterative(ltnb_3.getRoot(), 12);
    ltnb_3.visualizeBST();

    // test preOrder, inOrder, postOrder, levelOrder
    // expected result:
    //   preOrder : 6 3 1 0 2 4 5 9 8 7 11 10 12
    //    inOrder : 0 1 2 3 4 5 6 7 8 9 10 11 12
    // postOrder  : 0 2 1 5 4 3 7 8 10 12 11 9 6
    // levelOrder : 6 3 9 1 4 8 11 0 2 5 7 10 12
    // (note: results above do not show any '(', ')', '_' characters)
    cout << "  preOrder : ";
    ltnb_3.preOrder(ltnb_3.getRoot());
    cout << endl;
    cout << "   inOrder : ";
    ltnb_3.inOrder(ltnb_3.getRoot());
    cout << endl;
    cout << "postOrder  : ";
    ltnb_3.postOrder(ltnb_3.getRoot());
    cout << endl;
    cout << "levelOrder : ";
    ltnb_3.levelOrder(ltnb_3.getRoot());
    cout << "=============================================================\n";

    // test searchByValueRecursive, searchByValueIterative
    auto searchRes1 = ltnb_3.searchByValueRecursive(ltnb_3.getRoot(), 9);
    auto searchRes2 = ltnb_3.searchByValueRecursive(ltnb_3.getRoot(), 15);
    auto searchRes3 = ltnb_3.searchByValueIterative(ltnb_3.getRoot(), 9);
    auto searchRes4 = ltnb_3.searchByValueIterative(ltnb_3.getRoot(), 15);
    assert(searchRes1->data == 9);
    assert(searchRes1->leftChild->data == 8);
    assert(searchRes1->rightChild->data == 11);
    assert(searchRes2 == nullptr);
    assert(searchRes3 == searchRes1);
    assert(searchRes4 == nullptr);

    // test remove
    // scenario 1: remove a leaf node
    cout << "Before removing node 2:" << endl;
    ltnb_3.visualizeBST();
    ltnb_3.remove(ltnb_3.getRoot(), 2);
    cout << "After removing node 2:" << endl;
    ltnb_3.visualizeBST();
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a left child
    cout << "Before removing node 1:" << endl;
    ltnb_3.visualizeBST();
    ltnb_3.remove(ltnb_3.getRoot(), 1);
    cout << "After removing node 1:" << endl;
    ltnb_3.visualizeBST();
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a right child
    cout << "Before removing node 4:" << endl;
    ltnb_3.visualizeBST();
    ltnb_3.remove(ltnb_3.getRoot(), 4);
    cout << "After removing node 4:" << endl;
    ltnb_3.visualizeBST();
    cout << "=============================================================\n";

    // scenario 3: remove a complete internal node with two children
    cout << "Before removing node 6:" << endl;
    ltnb_3.visualizeBST();
    ltnb_3.remove(ltnb_3.getRoot(), 6);
    cout << "After removing node 6:" << endl;
    ltnb_3.visualizeBST();
    cout << "=============================================================\n";

    // test operator== overload
    LinkedTreeNodesBST<int> ltnb_4(10);
    ltnb_4.insertRecursive(ltnb_4.getRoot(), rootId, 5);
    ltnb_4.insertRecursive(ltnb_4.getRoot(), rootId, 7);
    ltnb_4.insertRecursive(ltnb_4.getRoot(), rootId, 12);
    ltnb_4.insertRecursive(ltnb_4.getRoot(), rootId, 11);
    ltnb_4.insertRecursive(ltnb_4.getRoot(), rootId, 14);
    LinkedTreeNodesBST<int> ltnb_5(10);
    ltnb_5.insertIterative(ltnb_5.getRoot(), 5);
    ltnb_5.insertIterative(ltnb_5.getRoot(), 7);
    ltnb_5.insertIterative(ltnb_5.getRoot(), 12);
    ltnb_5.insertIterative(ltnb_5.getRoot(), 11);
    ltnb_5.insertIterative(ltnb_5.getRoot(), 14);
    LinkedTreeNodesBST<int> ltnb_6(10);
    ltnb_6.insertIterative(ltnb_6.getRoot(), 5);
    ltnb_6.insertIterative(ltnb_6.getRoot(), 8);
    ltnb_6.insertIterative(ltnb_6.getRoot(), 12);
    ltnb_6.insertIterative(ltnb_6.getRoot(), 11);
    ltnb_6.insertIterative(ltnb_6.getRoot(), 14);
    assert(ltnb_4 == ltnb_5);
    assert(!(ltnb_4 == ltnb_6));

    // test getHeight
    assert(ltnb_1.getHeight() == 0);
    assert(ltnb_2.getHeight() == 7);
    assert(ltnb_3.getHeight() == 4);
    assert(ltnb_4.getHeight() == 3);
    assert(ltnb_5.getHeight() == 3);
    assert(ltnb_6.getHeight() == 3);

    // test isBST, minValue, maxValue
    assert(ltnb_6.isBST(ltnb_6.getRoot(), ltnb_6.minValue(), ltnb_6.maxValue()));
    auto tn11 = ltnb_6.searchByValueIterative(ltnb_6.getRoot(), 11);
    tn11->data = 9;
    assert(!ltnb_6.isBST(ltnb_6.getRoot(), ltnb_6.minValue(), ltnb_6.maxValue()));

    // test countNodes
    assert(ltnb_5.countNodes() == 6);
    assert(ltnb_4.countNodes() == 6);
    assert(ltnb_3.countNodes() == 9);
    assert(ltnb_2.countNodes() == 27);
    assert(ltnb_1.countNodes() == 0);

    return 0;
}

