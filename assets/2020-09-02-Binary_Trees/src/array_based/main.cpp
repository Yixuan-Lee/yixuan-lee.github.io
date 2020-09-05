#include <iostream>
#include <assert.h>
#include <stdexcept>
#include "ArrayBST.h"

using std::cout;
using std::endl;
using std::runtime_error;

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
    abst_3.insert(1);
    abst_3.insert(5);
    abst_3.insert(24);
    abst_3.insert(32);
    abst_3.insert(28);
    abst_3.insert(30);
    abst_3.insert(29);
    abst_3.insert(31);
    abst_3.insert(36);
    abst_3.insert(33);
    abst_3.insert(34);
    abst_3.insert(39);
    abst_3.insert(38);
    abst_3.insert(40);
    // scenario 1: remove a leaf node
    cout << "Before removing value 1:" << endl;
    assert(abst_3.countNodes() == 19);
    abst_3.visualizeBST();
    try {
        abst_3.remove(rootIndex, 1);
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After removing value 1:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 18);
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a left child
    cout << "Before removing value 8:" << endl;
    assert(abst_3.countNodes() == 18);
    abst_3.visualizeBST();
    try {
        abst_3.remove(rootIndex, 8);
    } catch (const runtime_error &e) {
        cout << e.what() << endl;
    }
    cout << "After removing value 8:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 17);
    cout << "=============================================================\n";

    // scenario 2: remove a partial internal node with a right child
    cout << "Before removing value 24:" << endl;
    assert(abst_3.countNodes() == 17);
    abst_3.visualizeBST();
    abst_3.remove(rootIndex, 24);
    cout << "After removing value 24:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 16);
    cout << "=============================================================\n";

    // scenario 3: remove a complete internal node with two children
    cout << "Before removing value 16:" << endl;
    assert(abst_3.countNodes() == 16);
    abst_3.visualizeBST();
    abst_3.remove(rootIndex, 16);
    cout << "After removing value 16:" << endl;
    abst_3.visualizeBST();
    assert(abst_3.countNodes() == 15);
    cout << "=============================================================\n";

    // test operator== overload
    ArrayBST<int, 0, 1> abst_4(5);
    abst_4.insert(4);
    abst_4.insert(3);
    abst_4.insert(2);
    abst_4.insert(7);
    abst_4.insert(6);
    abst_4.insert(8);
    ArrayBST<int, 0, 1> abst_5(5);
    abst_5.insert(4);
    abst_5.insert(3);
    abst_5.insert(2);
    abst_5.insert(7);
    abst_5.insert(6);
    abst_5.insert(8);
    ArrayBST<int, 0, 1> abst_6(5);
    abst_6.insert(4);
    abst_6.insert(3);
    abst_6.insert(2);
    abst_6.insert(7);
    abst_6.insert(6);
    abst_6.insert(9);
    assert((abst_4 == abst_5) == true);
    assert((abst_4 == abst_6) == false);

    // test getHeight
    assert(abst_1.getHeight() == 0);
    assert(abst_2.getHeight() == 5);
    assert(abst_3.getHeight() == 5);
    assert(abst_4.getHeight() == 4);
    assert(abst_5.getHeight() == 4);
    assert(abst_6.getHeight() == 4);

    // test minValue, maxValue
    assert(abst_3.minValue() == 2);
    assert(abst_3.maxValue() == 40);
    assert(abst_6.minValue() == 2);
    assert(abst_6.maxValue() == 9);

    // test countNodes
    assert(abst_1.countNodes() == 0);
    assert(abst_2.countNodes() == 31);
    assert(abst_3.countNodes() == 15);
    assert(abst_4.countNodes() == 7);
    assert(abst_5.countNodes() == 7);
    assert(abst_5.countNodes() == 7);

    return 0;
}
