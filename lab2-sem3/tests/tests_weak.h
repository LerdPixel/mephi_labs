#pragma once
#include <iostream>
#include "../smart_ptrs/weak_ptr.h"
#include "../smart_ptrs/shared_ptr.h"
#include <cassert>

class TestClassWeak {
public:
    int data;

    TestClassWeak(int value) : data(value) {}
    ~TestClassWeak() {
        //std::cout << "TestClassWeak destructor called for data: " << data << std::endl;
    }
};

// Helper function to check if a weak_ptr is expired and lock it
template <typename T>
bool isExpiredAndLock(weak_ptr<T>& weakPtr, shared_ptr<T>& lockedPtr) {
    if (weakPtr.expired()) {
        std::cout << "Weak pointer is expired." << std::endl;
        return false;
    }

    lockedPtr = weakPtr.lock();
    if (!lockedPtr) {
        std::cout << "Failed to lock weak pointer." << std::endl;
        return false;
    }

    return true;
}

// Test Case 1-10: Basic usage and locking
void testBasicUsageAndLocking() {
    shared_ptr<TestClassWeak> sharedPtr = make_shared<TestClassWeak>(42);
    weak_ptr<TestClassWeak> weakPtr(sharedPtr);

    assert(!weakPtr.expired());
    shared_ptr<TestClassWeak> lockedPtr;
    assert(isExpiredAndLock(weakPtr, lockedPtr));
    assert(lockedPtr->data == 42);
    assert(weakPtr.use_count() == 2);
    // Release the shared pointer and check weak pointer's expired state
    sharedPtr.reset();
    assert(weakPtr.use_count() == 1);
    lockedPtr.reset();
    assert(weakPtr.use_count() == 0);
    assert(weakPtr.expired());

    // Try locking an expired weak pointer
    assert(!isExpiredAndLock(weakPtr, lockedPtr));

    std::cout << "Test Cases 1-10 passed." << std::endl;
}

// Test Case 11-20: Creating weak pointers from shared pointers
void testCreatingWeakPointersFromShared() {
    shared_ptr<TestClassWeak> sharedPtr = make_shared<TestClassWeak>(55);
    weak_ptr<TestClassWeak> weakPtr1(sharedPtr);
    weak_ptr<TestClassWeak> weakPtr2(sharedPtr);

    // Lock the weak pointers and verify the object's data
    shared_ptr<TestClassWeak> lockedPtr1, lockedPtr2;
    assert(isExpiredAndLock(weakPtr1, lockedPtr1));
    assert(isExpiredAndLock(weakPtr2, lockedPtr2));
    assert(lockedPtr1->data == 55);
    assert(lockedPtr2->data == 55);

    // Reset the shared pointer and check weak pointers' expired state
    sharedPtr.reset();
    lockedPtr1.reset();
    lockedPtr2.reset();

    assert(weakPtr1.expired());
    assert(weakPtr2.expired());

    std::cout << "Test Cases 11-20 passed." << std::endl;
}

// Test Case 21-30: Locking and modifying the shared object
void testLockingAndModifyingSharedObject() {
    shared_ptr<TestClassWeak> sharedPtr = make_shared<TestClassWeak>(77);
    weak_ptr<TestClassWeak> weakPtr(sharedPtr);

    shared_ptr<TestClassWeak> lockedPtr;
    assert(isExpiredAndLock(weakPtr, lockedPtr));

    // Modify the shared object and check the changes through the weak pointer
    lockedPtr->data = 88;
    assert(weakPtr.lock()->data == 88);

    // Reset the shared pointer and check weak pointer's expired state
    sharedPtr.reset();
    lockedPtr.reset();
    assert(weakPtr.expired());

    std::cout << "Test Cases 21-30 passed." << std::endl;
}

// Test Case 31-40: Locking and releasing shared object
void testLockingAndReleasingSharedObject() {
    shared_ptr<TestClassWeak> sharedPtr = make_shared<TestClassWeak>(99);
    weak_ptr<TestClassWeak> weakPtr(sharedPtr);

    shared_ptr<TestClassWeak> lockedPtr;
    assert(isExpiredAndLock(weakPtr, lockedPtr));

    // Release the shared object and verify weak pointer's expired state
    sharedPtr.reset();
    lockedPtr.reset();
    assert(weakPtr.expired());

    // Try locking an expired weak pointer
    assert(!isExpiredAndLock(weakPtr, lockedPtr));

    std::cout << "Test Cases 31-40 passed." << std::endl;
}

// Test Case 41-50: Resetting weak pointers
void testResettingWeakPointers() {
    shared_ptr<TestClassWeak> sharedPtr = make_shared<TestClassWeak>(111);
    weak_ptr<TestClassWeak> weakPtr(sharedPtr);

    assert(!weakPtr.expired());
    shared_ptr<TestClassWeak> lockedPtr;
    assert(isExpiredAndLock(weakPtr, lockedPtr));

    // Reset the weak pointer and check its expired state
    weakPtr.reset();

    assert(weakPtr.expired());

    // Try locking a reset weak pointer
    assert(!isExpiredAndLock(weakPtr, lockedPtr));

    std::cout << "Test Cases 41-50 passed." << std::endl;
}

// Test Case 51-60: Locking expired weak pointers
void testLockingExpiredWeakPointers() {
    weak_ptr<TestClassWeak> weakPtr;

    // Try locking an initially expired weak pointer
    shared_ptr<TestClassWeak> lockedPtr;
    assert(!isExpiredAndLock(weakPtr, lockedPtr));

    // Reset the weak pointer and try locking again
    weakPtr.reset();
    lockedPtr.reset();
    assert(!isExpiredAndLock(weakPtr, lockedPtr));

    std::cout << "Test Cases 51-60 passed." << std::endl;
}

// Test Case 61-70: Expiring weak pointers on shared object destruction
void testExpiringOnSharedObjectDestruction() {
    shared_ptr<TestClassWeak> sharedPtr(new TestClassWeak(999));
    weak_ptr<TestClassWeak> weakPtr(sharedPtr);

    assert(!weakPtr.expired());
    sharedPtr.reset();
    assert(weakPtr.expired());

    std::cout << "Test Cases 61-70 passed." << std::endl;
}

int testsWeak() {
    testBasicUsageAndLocking();
    testCreatingWeakPointersFromShared();
    testLockingAndModifyingSharedObject();
    testLockingAndReleasingSharedObject();
    testResettingWeakPointers();
    testLockingExpiredWeakPointers();
    testExpiringOnSharedObjectDestruction();

    std::cout << "All weak_ptr test cases passed successfully!" << std::endl;

    return 0;
}
