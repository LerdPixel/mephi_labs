#pragma once
#include <iostream>
#include <cassert>
#include <functional>

#include "../smart_ptrs/unique_ptr.h"

template <typename T>
bool isValid(const unique_ptr<T>& ptr) {
    return ptr.get() != nullptr;
}

// Test Case 1-10: Basic construction and dereferencing
void testConstructionAndDereference() {
    unique_ptr<int> ptr1(new int(42));
    assert(*ptr1 == 42);
    assert(isValid(ptr1));

    unique_ptr<double> ptr2(new double(3.14));
    assert(*ptr2 == 3.14);
    assert(isValid(ptr2));

    unique_ptr<std::string> ptr3(new std::string("Hello"));
    assert(*ptr3 == "Hello");
    assert(isValid(ptr3));

    unique_ptr<char> ptr4(new char('A'));
    assert(*ptr4 == 'A');
    assert(isValid(ptr4));

    unique_ptr<bool> ptr5(new bool(true));
    assert(*ptr5 == true);
    assert(isValid(ptr5));

    unique_ptr<int> nullPtr;
    assert(!isValid(nullPtr));

    std::cout << "Test Cases 1-10 passed." << std::endl;
}

// Test Case 11-20: Move semantics
void testMoveSemantics() {
    unique_ptr<int> ptr1(new int(42));
    unique_ptr<int> ptr2 = std::move(ptr1);
    assert(ptr1.get() == nullptr);
    assert(*ptr2 == 42);
    assert(isValid(ptr2));

    unique_ptr<double> ptr3(new double(3.14));
    unique_ptr<double> ptr4(std::move(ptr3));
    assert(ptr3.get() == nullptr);
    assert(*ptr4 == 3.14);
    assert(isValid(ptr4));

    std::cout << "Test Cases 11-20 passed." << std::endl;
}

// Test Case 21-30: Reset and release
void testResetAndRelease() {
    unique_ptr<int> ptr1(new int(42));
    int* releasedPtr = ptr1.release();
    assert(ptr1.get() == nullptr);
    assert(*releasedPtr == 42);
    delete releasedPtr;

    unique_ptr<double> ptr2(new double(3.14));
    ptr2.reset(new double(2.71));
    assert(*ptr2 == 2.71);

    unique_ptr<std::string> ptr3(new std::string("Hello"));
    ptr3.reset();
    assert(!isValid(ptr3));

    std::cout << "Test Cases 21-30 passed." << std::endl;
}

// Test Case 41-50: Unique ownership
void testUniqueOwnership() {
    unique_ptr<int> ptr1(new int(42));
    assert(isValid(ptr1));
    unique_ptr<int> ptr2(std::move(ptr1));
    assert(!isValid(ptr1));
    assert(isValid(ptr2));
    unique_ptr<int> ptr3 = std::move(ptr2);
    assert(!isValid(ptr2));
    assert(isValid(ptr3));
    ptr3.reset();
    assert(!isValid(ptr3));

    unique_ptr<std::string> ptr4(new std::string("Hello"));
    unique_ptr<std::string> ptr5 = std::move(ptr4);
    assert(!isValid(ptr4));
    assert(isValid(ptr5));
    ptr5.reset();
    assert(!isValid(ptr5));

    std::cout << "Test Cases 41-50 passed." << std::endl;
}

// Test Case 51-60: Templated class with custom type
void testTemplatedClassWithCustomType() {
    struct CustomType {
        int value;
        CustomType(int val) : value(val) {}
    };

    unique_ptr<CustomType> ptr1(new CustomType(42));
    assert(ptr1->value == 42);

    unique_ptr<CustomType> ptr2 = std::move(ptr1);
    assert(ptr1.get() == nullptr);
    assert(ptr2->value == 42);

    std::cout << "Test Cases 51-60 passed." << std::endl;
}


int deleteCount = 0;
struct castomDeleter {
    void operator()(int* ptr) { 
        ++deleteCount;
        std::cout << "Custom deleter called for pointer with value: " << *ptr << std::endl;
        delete ptr;
    }
};
// Test Case 71-80: Custom deleter with lambda function
void testCustomDeleterWithLambda() {

    unique_ptr<int, castomDeleter> ptr1 = unique_ptr<int, castomDeleter>( new int(42) );
    assert(deleteCount == 0);
    ptr1.reset();
    assert(deleteCount == 1);

    unique_ptr<int, castomDeleter> ptr2(new int(100));
    unique_ptr<int, castomDeleter> ptr3 = std::move(ptr2);
    assert(deleteCount == 1);
    ptr3.reset();
    assert(deleteCount == 2);

    std::cout << "Test Cases 71-80 passed." << std::endl;
}

// Test Case 81-90: Conversion to bool and null pointers
void testConversionToBoolAndNullPointers() {
    unique_ptr<int> validPtr(new int(42));
    assert(static_cast<bool>(validPtr) == true);

    unique_ptr<int> nullPtr;
    assert(static_cast<bool>(nullPtr) == false);

    unique_ptr<int> releasedPtr = std::move(validPtr);
    assert(static_cast<bool>(validPtr) == false);
    assert(static_cast<bool>(releasedPtr) == true);

    std::cout << "Test Cases 81-90 passed." << std::endl;
}

// Test Case 91-100: Using custom types and complex objects
struct ComplexObject {
    int data;
    std::string description;

    ComplexObject(int d, const std::string& desc) : data(d), description(desc) {}
};

void testComplexObjects() {
    unique_ptr<ComplexObject> objPtr(new ComplexObject(42, "Custom Object"));
    assert(objPtr->data == 42);
    assert(objPtr->description == "Custom Object");

    unique_ptr<ComplexObject> movedPtr = std::move(objPtr);
    assert(objPtr.get() == nullptr);
    assert(movedPtr->data == 42);
    assert(movedPtr->description == "Custom Object");

    unique_ptr<ComplexObject> resetPtr(new ComplexObject(100, "Reset Object"));
    resetPtr.reset(new ComplexObject(200, "New Object"));
    assert(resetPtr->data == 200);
    assert(resetPtr->description == "New Object");

    std::cout << "Test Cases 91-100 passed." << std::endl;
}

int testsUnique() {
    testConstructionAndDereference();
    testMoveSemantics();
    testResetAndRelease();
    testUniqueOwnership();
    testTemplatedClassWithCustomType();
    testCustomDeleterWithLambda();
    testConversionToBoolAndNullPointers();
    testComplexObjects();

    std::cout << "All Unique Pointer test cases passed successfully!" << std::endl;

    return 0;
}
