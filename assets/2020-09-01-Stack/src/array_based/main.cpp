#include <iostream>
#include <assert.h>
#include "ArrayStack.h"

using std::cout;
using std::endl;

void testIntStack() {
    // test constructor
    ArrayStack<int> intStack{1};
    assert(intStack.toString() == "");

    // test push, top, toString
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.push(40);
    intStack.push(50);
    assert(intStack.top() == 50);
    assert(intStack.toString() == "50\n40\n30\n20\n10\n");

    assert(intStack.pop() == 50);
    assert(intStack.top() == 40);
    assert(intStack.toString() == "40\n30\n20\n10\n");

    // test clear
    intStack.clear();
    assert(intStack.toString() == "");

    // test copy constructor, size, isEmpty
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.push(40);
    intStack.push(50);
    intStack.push(60);
    ArrayStack<int> temp{intStack};
    assert(temp.toString() == "60\n50\n40\n30\n20\n10\n");
    assert(temp.size() == 6);
    assert(temp.top() == 60);
    assert(temp.isEmpty() == false);
    assert(temp.pop() == 60);
    assert(temp.size() == 5);
    assert(temp.pop() == 50);
    assert(temp.toString() == "40\n30\n20\n10\n");

    // test copy assignment operator
    assert(intStack.toString() == "60\n50\n40\n30\n20\n10\n");
    intStack = temp;
    assert(intStack.toString() == "40\n30\n20\n10\n");

    // test move constructor
    ArrayStack<int> temp2{std::move(temp)};
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
