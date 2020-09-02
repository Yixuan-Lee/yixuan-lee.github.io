#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <array>
#include <string>
#include <stdexcept>

using std::array;
using std::string;

/**
 * Array based Stack
 *
 * @tparam T  generic type
 *            assuming that T has implemented operator[], operator=, operator()
 */
template <typename T>
class ArrayStack {
public:
    // constructor
    explicit ArrayStack(size_t size = 100);

    /////////////////////////  Big Five  /////////////////////////
    // 1. destructor
    virtual ~ArrayStack();

    // 2. copy constructor
    ArrayStack(const ArrayStack &);

    // 3. copy assignment operator=
    ArrayStack& operator=(const ArrayStack &);

    // 4. move constructor
    ArrayStack(ArrayStack &&) noexcept;

    // 5. move assignment operator=
    ArrayStack& operator=(ArrayStack &&) noexcept;
    //////////////////////////////////////////////////////////////

    ///////////////////  Principle Operations  ///////////////////
    void push(T e);

    T pop();
    //////////////////////////////////////////////////////////////

    ///////////////////  Auxiliary Operations  ///////////////////
    bool isEmpty() const;

    size_t size() const;

    T top() const;

    void clear();

    string toString() const;
    //////////////////////////////////////////////////////////////


private:
    T *arr;

    size_t count {};

    size_t capacity {};

    ///////////////////  Auxiliary Functions  ////////////////////
    void deepcopy(const ArrayStack &);

    void deepmove(ArrayStack &);

    void doublesize();
    //////////////////////////////////////////////////////////////
};

///////////////////  Function Implementation  ///////////////////

template<typename T>
ArrayStack<T>::ArrayStack(size_t size) : arr {new T[size]}, count {0}, capacity {size} {

}

/////////////////////////  Big Five  /////////////////////////
// 1. destructor
template<typename T>
ArrayStack<T>::~ArrayStack() {
    delete[] this->arr;
    this->arr = nullptr;    // defensive programming
}

// 2. copy constructor
template<typename T>
ArrayStack<T>::ArrayStack(const ArrayStack &as) {
    deepcopy(as);
}

// 3. copy assignment operator=
template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack &as) {
    // check self-assignment
    if (this == &as) {
        return *this;
    }

    deepcopy(as);
    return *this;
}

// 4. move constructor
template<typename T>
ArrayStack<T>::ArrayStack(ArrayStack &&as) noexcept {
    deepmove(as);
}

// 5. move assignment operator=
template<typename T>
ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack &&as) noexcept {
    // check self-assignment
    if (this == &as) {
        return *this;
    }

    deepmove(as);
    return *this;
}

//////////////////////////////////////////////////////////////

///////////////////  Principle Operations  ///////////////////
template<typename T>
void ArrayStack<T>::push(T e) {
    if (count == capacity) {
        // double the capacity and copy
        doublesize();
    }
    this->arr[this->count++] = e;
}

template<typename T>
T ArrayStack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    T ret = this->arr[this->count - 1];
    this->count--;
    return ret;
}
//////////////////////////////////////////////////////////////

///////////////////  Auxiliary Operations  ///////////////////
template<typename T>
bool ArrayStack<T>::isEmpty() const {
    return this->size() == 0;
}

template<typename T>
size_t ArrayStack<T>::size() const {
    return this->count;
}

template<typename T>
T ArrayStack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return this->arr[this->count - 1];
}

template<typename T>
void ArrayStack<T>::clear() {
    this->count = 0;
}

template<typename T>
string ArrayStack<T>::toString() const {
    if (isEmpty()) {
        return "";
    }

    string ret;
    for (int i = count - 1; i >= 0; --i) {
        ret += std::to_string(this->arr[i]) + "\n";
    }
    return ret;
}
//////////////////////////////////////////////////////////////

///////////////////  Auxiliary Functions  ////////////////////
template<typename T>
void ArrayStack<T>::deepcopy(const ArrayStack &as) {
    // de-allocation
    delete[] this->arr;

    this->arr = new T[as.count];
    // element-wise copy
    for (size_t i = 0; i < as.count; ++i) {
        this->arr[i] = as.arr[i];
    }
    this->count = as.count;
}

template<typename T>
void ArrayStack<T>::deepmove(ArrayStack &as) {
    // de-allocation
    delete[] this->arr;

    this->arr = new T[as.count];
    // element-wise move
    for (size_t i = 0; i < as.count; ++i) {
        this->arr[i] = std::move(as.arr[i]);
    }
    this->count = as.count;

    // reset as to stable state
    as.arr = nullptr;
    as.count = 0;
}

template<typename T>
void ArrayStack<T>::doublesize() {
    size_t doubleCapacity = 2 * this->capacity;

    // allocate new array
    T *temp = this->arr;
    this->arr = new T[doubleCapacity];

    // element-wise copy
    for (size_t i = 0; i < this->count; ++i) {
        this->arr[i] = temp[i];
    }

    // de-allocation
    delete temp;
}
//////////////////////////////////////////////////////////////

#endif //ARRAY_STACK_H
