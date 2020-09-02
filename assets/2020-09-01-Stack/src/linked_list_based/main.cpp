#include <iostream>
#include <assert.h>
#include "LinkedListStack.h"

using std::cout;
using std::endl;

void testIntStack() {
    // test constructor
    LinkedListStack<int> lls1;
    assert(lls1.toString() == "");

    // test push, top, toString
    lls1.push(10);
    lls1.push(20);
    lls1.push(30);
    lls1.push(40);
    lls1.push(50);
    assert(lls1.top() == 50);
    assert(lls1.toString() == "50\n40\n30\n20\n10\n");

    assert(lls1.pop() == 50);
    assert(lls1.top() == 40);
    assert(lls1.toString() == "40\n30\n20\n10\n");

    // test clear
    lls1.clear();
    assert(lls1.toString() == "");

    // test copy constructor, size, isEmpty
    lls1.push(10);
    lls1.push(20);
    lls1.push(30);
    lls1.push(40);
    lls1.push(50);
    lls1.push(60);
    LinkedListStack<int> temp{lls1};
    assert(temp.toString() == "60\n50\n40\n30\n20\n10\n");
    assert(temp.size() == 6);
    assert(temp.top() == 60);
    assert(temp.isEmpty() == false);
    assert(temp.pop() == 60);
    assert(temp.size() == 5);
    assert(temp.pop() == 50);
    assert(temp.toString() == "40\n30\n20\n10\n");

    // test copy assignment operator
    assert(lls1.toString() == "60\n50\n40\n30\n20\n10\n");
    lls1 = temp;
    assert(lls1.toString() == "40\n30\n20\n10\n");

    // test move constructor
    LinkedListStack<int> temp2{std::move(temp)};
    assert(temp.isEmpty() == true);
    assert(temp.toString() == "");
    assert(temp2.toString() == "40\n30\n20\n10\n");
    assert(temp2.size() == 4);

    // test move assignment operator
    temp = std::move(temp2);
    assert(temp.isEmpty() == false);
    assert(temp.toString() == "40\n30\n20\n10\n");
    assert(temp2.isEmpty() == true);
    assert(temp2.toString() == "");
}

int main() {
    testIntStack();

    return 0;
}