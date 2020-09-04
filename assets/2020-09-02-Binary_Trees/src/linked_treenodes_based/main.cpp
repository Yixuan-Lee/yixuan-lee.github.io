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

    // test insertRecursive, insertIterative
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
    cout << endl;

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
    cout << endl;


    return 0;
}

