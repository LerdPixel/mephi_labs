#pragma once
#include <gtest/gtest.h>
#include "../smart_ptrs/shared_ptr.h"
#include "../HashTable.h"

struct HashTableTests : public testing::Test {
    shared_ptr<HashTable<int, int>> htp;
    void SetUp() {
        htp = shared_ptr<HashTable<int, int>>(new HashTable<int, int>(4));
    }
    void TearDown() {
    }
};

TEST_F(HashTableTests, HashTableTests_Initialization) {
    auto newHashT = make_shared<HashTable<int, int>>(10);
    ASSERT_EQ(newHashT->GetLength(), 0);
    ASSERT_EQ(newHashT->GetCapacity(), 10);
}
TEST_F(HashTableTests, HashTableTests_Addition) {
    htp->Add(2, 3);
    ASSERT_EQ(htp->Get(2), 3);
}
TEST_F(HashTableTests, HashTableTests_Rearrangement) {
    htp->Add(2, 3);
    htp->Add(3, 3);
    htp->Add(4, 3);
    htp->Add(5, 3);
    htp->Add(6, 3);
    std::cout << htp->GetCapacity() << '\n';
    ASSERT_EQ(htp->GetLength(), 5);
    ASSERT_EQ(htp->GetCapacity(), 8);
}
TEST_F(HashTableTests, HashTableTests_Set) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    htp->Set(2, 4);
    ASSERT_EQ(htp->Get(2), 4);
}
TEST_F(HashTableTests, HashTableTests_Set_2) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    htp->Set(4, 4);
    ASSERT_EQ(htp->Get(4), 4);
}
TEST_F(HashTableTests, HashTableTests_Remove_1) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    htp->Remove(4);
    ASSERT_EQ(htp->GetLength(), 1);
    ASSERT_EQ(htp->GetCapacity(), 2);
}
TEST_F(HashTableTests, HashTableTests_Remove_2) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    try {
        htp->Remove(3);
    } catch(const std::exception& oor) {
        ASSERT_EQ(oor.what(), std::string("key not found"));
    }
}
TEST_F(HashTableTests, HashTableTests_Remove_and_Rearrangement) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    htp->Add(5, 5);
    htp->Add(6, 5);
    htp->Add(7, 5);
    ASSERT_EQ(htp->GetLength(), 5);
    ASSERT_EQ(htp->GetCapacity(), 8);
    htp->Remove(4);
    htp->Remove(5);
    ASSERT_EQ(htp->GetCapacity(), 8);
    htp->Remove(6);
    ASSERT_EQ(htp->GetCapacity(), 4);
}
TEST_F(HashTableTests, HashTableTests_ContainsKey) {
    htp->Add(2, 3);
    htp->Add(4, 5);
    ASSERT_TRUE(htp->ContainsKey(4));
    ASSERT_TRUE(htp->ContainsKey(2));
    ASSERT_FALSE(htp->ContainsKey(3));
}