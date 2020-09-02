#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

template<typename T>
class LinkedListStack {
public:
    // constructor
    LinkedListStack();

    /////////////////////////  Big Five  /////////////////////////
    // 1. destructor
    virtual ~LinkedListStack();

    // 2. copy constructor
    LinkedListStack(const LinkedListStack &);

    // 3. copy assignment operator=
    LinkedListStack& operator=(const LinkedListStack &);

    // 4. move constructor
    LinkedListStack(LinkedListStack &&) noexcept;

    // 5. move assignment operator=
    LinkedListStack& operator=(LinkedListStack &&) noexcept;
    //////////////////////////////////////////////////////////////


    ///////////////////  Principle Operations  ///////////////////
    void push(T e);

    T pop();
    //////////////////////////////////////////////////////////////

    ///////////////////  Auxiliary Operations  ///////////////////
    bool isEmpty() const;

//    bool isFull() const;

    size_t size() const;

    T top() const;

    void clear();

    string toString() const;
    //////////////////////////////////////////////////////////////
private:
    struct Node {
        T data;
        Node *next;

        // Node constructor
        explicit Node(T data, Node *next = nullptr) : data {data}, next {next} {
        }
    };

    Node *head;

    size_t count {};

    ///////////////////  Auxiliary Functions  ////////////////////
    void deepcopy(const LinkedListStack &);

    void deepmove(LinkedListStack &);

//    void doublesize();
    //////////////////////////////////////////////////////////////
};

///////////////////  Function Implementation  ///////////////////
// constructor
template<typename T>
LinkedListStack<T>::LinkedListStack() {
    count = 0;
    head = nullptr;
}

/////////////////////////  Big Five  /////////////////////////
// 1. destructor
template<typename T>
LinkedListStack<T>::~LinkedListStack() {
    while (!isEmpty()) {
        pop();
    }
}

// 2. copy constructor
template<typename T>
LinkedListStack<T>::LinkedListStack(const LinkedListStack &lls) {
    deepcopy(lls);
}

// 3. copy assignment operator=
template<typename T>
LinkedListStack<T>& LinkedListStack<T>::operator=(const LinkedListStack &lls) {
    // check self-assignment
    if (this == &lls) {
        return *this;
    }

    deepcopy(lls);
    return *this;
}

// 4. move constructor
template<typename T>
LinkedListStack<T>::LinkedListStack(LinkedListStack &&lls) noexcept {
    deepmove(lls);
}

// 5. move assignment operator=
template<typename T>
LinkedListStack<T>& LinkedListStack<T>::operator=(LinkedListStack &&lls) noexcept {
    // check self-assignment
    if (this == &lls) {
        return *this;
    }

    deepmove(lls);
    return *this;
}

/////////////////////////////////////////////////////////////////

///////////////////  Principle Operations  ///////////////////
template<typename T>
void LinkedListStack<T>::push(T e) {
    // create a new Node
    Node *newNode = new Node(e, head);
    // redirect head
    head = newNode;
    count++;
}

template<typename T>
T LinkedListStack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    T ret = head->data;
    head = head->next;
    count--;
    return ret;
}

/////////////////////////////////////////////////////////////////

///////////////////  Auxiliary Operations  ///////////////////
template<typename T>
bool LinkedListStack<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
size_t LinkedListStack<T>::size() const {
    return count;
}

template<typename T>
T LinkedListStack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return head->data;
}

template<typename T>
void LinkedListStack<T>::clear() {
    while (!isEmpty()) {
        pop();
    }
}

template<typename T>
string LinkedListStack<T>::toString() const {
    if (isEmpty()) {
        return "";
    }

    string ret;
    for (Node *it = head; it != nullptr; it = it->next) {
        ret += std::to_string(it->data) + "\n";
    }
    return ret;
}

/////////////////////////////////////////////////////////////////

////////////////////  Auxiliary Functions  //////////////////////
template<typename T>
void LinkedListStack<T>::deepcopy(const LinkedListStack &lls) {
    // empty the stack
    clear();

    // element-wise copy
    // store all the elements in lls
    vector<T> temp;
    for (Node *it = lls.head; it != nullptr; it = it->next) {
        // store a deep copy
        T t {it->data};
        temp.push_back(t);
    }

    // element-wise push (push from rear to head)
    for (int i = temp.size() - 1; i >= 0; --i) {
        push(temp.at(i));
    }
}

template<typename T>
void LinkedListStack<T>::deepmove(LinkedListStack &lls) {
    // empty the stack
    clear();

    // element-wise copy
    // store all the elements in lls
    vector<T> temp;
    for (Node *it = lls.head; it != nullptr; it = it->next) {
        // store a deep copy
        temp.push_back(std::move(it->data));
    }

    // element-wise push (push from rear to head)
    for (int i = temp.size() - 1; i >= 0; --i) {
        push(std::move(temp.at(i)));
    }

    // reset lls to stable state
    lls.clear();
}
/////////////////////////////////////////////////////////////////


#endif //LINKEDLISTSTACK_H
