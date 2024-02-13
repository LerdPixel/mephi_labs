#pragma once
#include <gtest/gtest.h>
#include "../SortedSequence.h"
#include "../Sequence.h"
#include "../ArraySequence.h"

struct SortedSequenceTests : public testing::Test {
    shared_ptr<ArraySequence<int>> as;
    SortedSequence<int> ss;

    void SetUp() {
        int a[] = {1,4,5,6,-1};
        as = make_shared<ArraySequence<int>>(a, 5);
        ss = SortedSequence<int>(*as);
        ss.Add(-2);
    }
    void TearDown() {
    }
};

TEST_F(SortedSequenceTests, SortedSequence_Initialization) {
    ASSERT_EQ(ss.IndexOf(3), -1);
}
TEST_F(SortedSequenceTests, SortedSequence_IndexOf_1) {
    ASSERT_EQ(ss.IndexOf(4), 3);
}
TEST_F(SortedSequenceTests, SortedSequence_IndexOf_2) {
    ASSERT_EQ(ss.IndexOf(-1), 1);
}
TEST_F(SortedSequenceTests, SortedSequence_IndexOf_ultimate_1) {
    ASSERT_EQ(ss.IndexOf(-2), 0);
}
TEST_F(SortedSequenceTests, SortedSequence_IndexOf_ultimate_2) {
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
TEST_F(SortedSequenceTests, SortedSequence_Release_1) {
    int b[] = {-2,-1,1,4,5,6};
/*     printSequenceScalar<int>(*ss.Release());
 */    ASSERT_TRUE(*(ss.GetValues()) == ArraySequence<int>(b, 6));
}
