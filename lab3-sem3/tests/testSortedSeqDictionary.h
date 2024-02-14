#pragma once
#include <gtest/gtest.h>
#include "../SortedSequenceDictionary.h"
#include "../SortedSequence.h"
#include "../Sequence.h"
#include "../ArraySequence.h"

struct SortedSequenceDictionaryTests : public testing::Test {
    shared_ptr<Sequence<int>> ks;
    shared_ptr<Sequence<int>> vs; 
    shared_ptr<SortedSequenceDictionary<int, int>> dd;

    void SetUp() {
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
/*
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_IndexOf_ultimate_1) {
    ASSERT_EQ(ss.IndexOf(-2), 0);
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_IndexOf_ultimate_2) {
    ASSERT_EQ(ss.IndexOf(6), 5);
}
template <typename T>
void printSequenceScalar(Sequence<T>& seq) {
    auto e = seq.GetEnumerator();
    while (e->next()) {
        std::cout << *(*e) << ' ';
    }
    std::cout << std::endl;
}
TEST_F(SortedSequenceDictionaryTests, SortedSequenceDictionary_Release_1) {
    int b[] = {-2,-1,1,4,5,6};
   ASSERT_TRUE(*(ss.GetValues()) == ArraySequence<int>(b, 6));
}
*/