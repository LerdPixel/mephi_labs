#pragma once
#include <gtest/gtest.h>
/* #include "../Pair.h"
#include "../SortedPointerSequence.h"
#include "../Sequence.h"
#include "../ArraySequence.h"

struct SortedPointerSequenceTests : public testing::Test {
    shared_ptr<ArraySequence<Pair<int, int>>> as;
    SortedPointerSequence<Pair<int, int>> ss;
    Pair<int, int> *a;
    void SetUp() {
        size_t size = 5;
        a = new  Pair<int,int> [size];
        a[0] = Pair<int, int>(1,3);
        a[1] = Pair<int, int>(1,4);
        a[2] = Pair<int, int>(5,0);
        a[3] = Pair<int, int>(6,2);
        a[4] = Pair<int, int>(-1,9);
        as = make_shared<ArraySequence<Pair<int, int>>>(a, 5);
        ss = SortedPointerSequence<Pair<int, int>>(*as);
        ss.Add(Pair<int, int>(-2,4));
    }
    void TearDown() {
        delete a;
    }
};

TEST_F(SortedPointerSequenceTests, SortedPointerSequence_Initialization) {
    ASSERT_EQ(ss.IndexOf(Pair<int, int>(3,0)), -1);
}
TEST_F(SortedPointerSequenceTests, SortedPointerSequence_IndexOf_1) {
    ASSERT_EQ(ss.IndexOf(Pair<int, int>(4,0)), 3);
}

 */