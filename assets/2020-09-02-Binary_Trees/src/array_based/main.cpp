#include <iostream>
#include <assert.h>
#include "ArrayBST.h"

using std::cout;
using std::endl;

const int rootIndex = 1;

int main() {
    // test default constructor
    ArrayBST<int, 0> abst_1;
    assert(abst_1.countNodes() == 0);
    assert(abst_1.isEmpty() == true);

    // test constructor
    ArrayBST<int, 0, 1> abst_2(16);
    assert(abst_2.countNodes() == 1);
    assert(abst_2.isEmpty() == false);
    abst_2.visualizeBST();
    cout << "=============================================================\n";

    // test insert, visualizeBST, doublesize, getHeight
    // insert values in the left subtree
    abst_2.insert(8);
    abst_2.insert(4);
    abst_2.insert(12);
    abst_2.insert(2);
    abst_2.insert(6);
    abst_2.insert(10);
    abst_2.insert(14);
    abst_2.insert(1);
    abst_2.insert(3);
    abst_2.insert(5);
    abst_2.insert(7);
    abst_2.insert(9);
    abst_2.insert(11);
    abst_2.insert(13);
    abst_2.insert(15);
    // insert values in the right subtree
    abst_2.insert(24);
    abst_2.insert(20);
    abst_2.insert(28);
    abst_2.insert(18);
    abst_2.insert(22);
    abst_2.insert(26);
    abst_2.insert(30);
    abst_2.insert(17);
    abst_2.insert(19);
    abst_2.insert(21);
    abst_2.insert(23);
    abst_2.insert(25);
    abst_2.insert(27);
    abst_2.insert(29);
    abst_2.insert(31);
    abst_2.visualizeBST();
    cout << "    height : " << abst_2.getHeight() << endl;

    // test preOrder, inOrder, postOrder, levelOrder
    cout << "  preOrder : ";
    abst_2.preOrder(rootIndex);
    cout << endl;
    cout << "   inOrder : ";
    abst_2.inOrder(rootIndex);
    cout << endl;
    cout << "postOrder  : ";
    abst_2.postOrder(rootIndex);
    cout << endl;
    cout << "levelOrder : ";
    abst_2.levelOrder(rootIndex);
    cout << endl;
    cout << "=============================================================\n";

    int searchRes1 = abst_2.searchByValue(5);
    int searchRes2 = abst_2.searchByValue(15);
    int searchRes3 = abst_2.searchByValue(25);
    int searchRes4 = abst_2.searchByValue(32);
    assert(searchRes1 == 5);
    assert(searchRes2 == 15);
    assert(searchRes3 == 25);
    assert(searchRes4 == -1);

    // test remove
    ArrayBST<int, 0, 1> abst_3(16);
    abst_3.insert(8);
    abst_3.insert(4);
    abst_3.insert(2);
    abst_3.insert(6);
    abst_3.insert(5);
    abst_3.insert(24);
    abst_3.insert(28);
    abst_3.insert(26);
    abst_3.insert(30);
    abst_3.insert(27);
    abst_3.insert(29);
    abst_3.insert(31);
    // scenario 1: remove a leaf node
    cout << "Before removing value 5:" << endl;
    assert(abst_3.countNodes() == 13);
    abst_3.visualizeBST();
    abst_3.remove(rootIndex, 5);
    cout << "After removing value 5:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 12);
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a left child
    cout << "Before removing value 8:" << endl;
    assert(abst_3.countNodes() == 12);
    abst_3.visualizeBST();
    abst_3.remove(rootIndex, 8);
    cout << "After removing value 8:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 11);
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a right child
    cout << "Before removing value 24:" << endl;
    assert(abst_3.countNodes() == 11);
    abst_3.visualizeBST();
    abst_3.remove(rootIndex, 24);   // TODO: buggy
    cout << "After removing value 24:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 10);
    cout << "=============================================================\n";

    // scenario 3: remove a complete internal node with two children
//    cout << "Before removing value 16:" << endl;
//    assert(abst_3.countNodes() == 10);
//    abst_3.visualizeBST();
//    abst_3.remove(rootIndex, 16);
//    cout << "After removing value 16:" << endl;
//    abst_3.visualizeBST();
//    assert(abst_3.countNodes() == 9);
//    cout << "=============================================================\n";

    return 0;
}
