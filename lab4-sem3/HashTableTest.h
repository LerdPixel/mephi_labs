#pragma once
#include <gtest/gtest.h>
#include "HashTable.h"

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