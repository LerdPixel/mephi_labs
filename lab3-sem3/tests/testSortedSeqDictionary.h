#pragma once
#include <gtest/gtest.h>
#include "../SortedSequenceDictionary.h"
#include "../SortedSequence.h"
#include "../Sequence.h"
#include "../ArraySequence.h"

struct SortedSequenceDictionaryTests : public testing::Test {
    shared_ptr<Sequence<int>> ks;
    shared_ptr<Sequence<int>> vs; 
    shared_ptr<Sequence<std::string>> ss;
    shared_ptr<Sequence<int>> sv; 
    shared_ptr<SortedSequenceDictionary<int, int>> dd;
    shared_ptr<SortedSequenceDictionary<std::string, int>> ssd;
    void SetUp() {
        std::string skeys[] = {"15", "jaba", "slavik"};
        int sva[] = {1, 2, 3};
        ss = shared_ptr<Sequence<std::string>>(new ArraySequence<std::string>(skeys, 3));
        sv = shared_ptr<Sequence<int>>(new ArraySequence<int>(sva, 3));
        ssd = shared_ptr<SortedSequenceDictionary<std::string, int>>(new SortedSequenceDictionary<std::string, int>(ss, sv));
        int ka[] = {1,4,5,6,-1};
        int va[] = {11,14,15,16,-11};
        ks = shared_ptr<Sequence<int>>(new ArraySequence<int>(ka, 5));
        vs = shared_ptr<Sequence<int>>(new ArraySequence<int>(va, 5));
        dd = make_shared<SortedSequenceDictionary<int, int>>(ks, vs);
    }
    void TearDown() {
    }
};

TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_Initialization) {
    ASSERT_EQ(dd->GetLength(), 5);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_Initialization_2) {
    SortedSequenceDictionary<int, int> dd2;
    ASSERT_EQ(dd2.GetLength(), 0);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_Length_1) {
    dd->Add(3, 13);
    ASSERT_EQ(dd->GetLength(), 6);
}

TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_Add_1) {
    SortedSequenceDictionary<int, int> dd2;
    dd2.Add(1,2);
    ASSERT_EQ(dd2.GetLength(), 1);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_operator_1) {
    ASSERT_EQ((*dd)[6], 16);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_operator_2) {
    (*dd)[6] = -16;
    ASSERT_EQ((*dd)[6], -16);
}
/* TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_operator_3) {
    (*dd)[7] = 17;
    ASSERT_EQ((*dd)[6], -16);
} */
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_set_1) {
    dd->Set(5, -15);
    ASSERT_EQ(dd->Get(5), -15);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_remove_1) {
    dd->Remove(5);
    ASSERT_EQ(dd->GetLength(), 4);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_remove_2) {
    dd->Remove(6);
    dd->Remove(-1);
    ASSERT_EQ(dd->GetLength(), 3);
}

TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_remove_3) {
    dd->Remove(6);
    dd->Remove(-1);
    ASSERT_EQ(dd->GetLength(), 3);
    try {
        dd->Get(6);
    } catch(const std::exception& oor) {
        ASSERT_EQ(oor.what(), std::string("bad_optional_access"));
    }
}

TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_remove_4) {
    dd->Remove(5);
    dd->Remove(-1);
    ASSERT_EQ(dd->Get(4), 14);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_IndexOf_tryCatch_1) {
    try {
        dd->Get(-2);
    } catch(const std::exception& oor) {
        ASSERT_EQ(oor.what(), std::string("bad_optional_access"));
    }
}