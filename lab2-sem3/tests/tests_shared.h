#pragma once
#include <iostream>
#include <cstddef>
#include "../smart_ptrs/unique_ptr.h"
#include "../smart_ptrs/weak_ptr.h"
#include <cassert>
class MyClass {
public:
    MyClass(int value) : data(value) {}
    int getData() const { return data; }

private:
    int data;
};

template <typename T>
bool isValid(const shared_ptr<T>& ptr) {
    return ptr.get() != nullptr;
}


int testsShared()
{
   // Test Case 1: Creating a shared_ptr and accessing its data
    shared_ptr<MyClass> ptr1 = make_shared<MyClass>(42);
    assert(ptr1->getData() == 42);
    std::cout << "Test Case 1 passed." << std::endl;

        // Test Case 2: Copying shared_ptr and verifying shared ownership
    shared_ptr<MyClass> ptr2 = ptr1;
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
    std::cout << "Test Case 2 passed." << std::endl;
    
        // Test Case 3: Resetting shared_ptr and checking use_count
    ptr1.reset();
    assert(ptr1.use_count() == 0);
    assert(ptr2.use_count() == 1);
    std::cout << "Test Case 3 passed." << std::endl;

    // Test Case 5: Comparing shared_ptrs
    shared_ptr<MyClass> ptr4 = make_shared<MyClass>(100);
    shared_ptr<MyClass> ptr5 = ptr4;
    assert(ptr4 == ptr5);
    std::cout << "Test Case 5 passed." << std::endl;
    
    shared_ptr<MyClass> nullPtr;
    assert(!isValid(nullPtr));
    std::cout << "Test Case 1 passed." << std::endl;

    // Test Case 2: Creating a shared_ptr with make_shared and nullptr
    shared_ptr<MyClass> nullPtr2(nullptr);
    assert(!isValid(nullPtr2));
    std::cout << "Test Case 2 passed." << std::endl;

    // Test Case 4: Creating a shared_ptr with new and checking use_count
    shared_ptr<MyClass> ptr20(new MyClass(88));
    assert(isValid(ptr20));
    assert(ptr20.use_count() == 1);
    std::cout << "Test Case 4 passed." << std::endl;

    // Test Case 5: Resetting shared_ptr to nullptr
    ptr1.reset();
    assert(!isValid(ptr1));
    std::cout << "Test Case 5 passed." << std::endl;

    // Test Case 6: Using shared_ptr in a container
    std::vector<shared_ptr<MyClass>> ptrContainer;
    ptrContainer.push_back(make_shared<MyClass>(10));
    ptrContainer.push_back(make_shared<MyClass>(20));
    assert(ptrContainer.size() == 2);
    std::cout << "Test Case 6 passed." << std::endl;


 // Test Case 11-30: Creating and copying shared_ptr instances
    for (int i = 0; i < 20; ++i) {
        shared_ptr<MyClass> ptr = make_shared<MyClass>(i);
        assert(isValid(ptr));
        assert(ptr.use_count() == 1);
        shared_ptr<MyClass> copyPtr = ptr;
        assert(copyPtr.use_count() == 2);
        assert(ptr->getData() == i);
    }
    std::cout << "Test Cases 11-30 passed." << std::endl;

    // Test Case 31-40: Move semantics and shared_ptr
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> sourcePtr = make_shared<MyClass>(i);
        assert(isValid(sourcePtr));
        assert(sourcePtr.use_count() == 1);
        shared_ptr<MyClass> destPtr = std::move(sourcePtr);
        assert(!isValid(sourcePtr));
        assert(isValid(destPtr));
        assert(destPtr.use_count() == 1);
        assert(destPtr->getData() == i);
    }
    std::cout << "Test Cases 31-40 passed." << std::endl;

    // Test Case 41-50: Resetting shared_ptr with a new object
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> ptr = make_shared<MyClass>(i);
        assert(isValid(ptr));
        assert(ptr.use_count() == 1);
        ptr.reset(new MyClass(i * 2));
        assert(isValid(ptr));
        assert(ptr.use_count() == 1);
        assert(ptr->getData() == i * 2);
    }
    std::cout << "Test Cases 41-50 passed." << std::endl;

    // Test Case 51-60: Comparing shared_ptrs
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> ptr1 = make_shared<MyClass>(i);
        shared_ptr<MyClass> ptr2 = make_shared<MyClass>(i);
        assert(ptr1 != ptr2);
    }
    std::cout << "Test Cases 51-60 passed." << std::endl;

    // Test Case 61-70: Checking use_count after reset and copy
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> ptr1 = make_shared<MyClass>(i);
        shared_ptr<MyClass> ptr2 = ptr1;
        assert(ptr1.use_count() == 2);
        ptr1.reset();
        assert(ptr2.use_count() == 1);
        ptr2.reset();
        assert(ptr2.use_count() == 0);
    }
    std::cout << "Test Cases 61-70 passed." << std::endl;

    // Test Case 71-80: Using make_shared with custom constructor arguments
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> ptr = make_shared<MyClass>(i * 2);
        assert(isValid(ptr));
        assert(ptr.use_count() == 1);
        assert(ptr->getData() == i * 2);
    }
    std::cout << "Test Cases 71-80 passed." << std::endl;

    // Test Case 81-90: Using shared_ptr with std::unique_ptr
    for (int i = 0; i < 10; ++i) {
        shared_ptr<unique_ptr<MyClass>> ptr = make_shared<unique_ptr<MyClass>>(make_unique<MyClass>(i));
        assert(isValid(ptr));
        assert((*ptr)->getData() == i);
    }
    std::cout << "Test Cases 81-90 passed." << std::endl;

    // Test Case 91-100: Using shared_ptr with std::weak_ptr
    for (int i = 0; i < 10; ++i) {
        shared_ptr<MyClass> sharedPtr = make_shared<MyClass>(i);
        weak_ptr<MyClass> weakPtr = sharedPtr;
        assert(weakPtr.use_count() == 1);
        sharedPtr.reset();
        assert(weakPtr.use_count() == 0);
        assert(weakPtr.expired());
    }
    std::cout << "Test Cases 91-100 passed." << std::endl;

    std::cout << "All shared_ptr test cases passed successfully!" << std::endl;

    return 0;
}