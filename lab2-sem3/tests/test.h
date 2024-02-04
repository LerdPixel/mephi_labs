#ifndef TEST_H
#define TEST_H
#include <gtest/gtest.h>
#include "../ICollection.h"
#include "../DynamicArray.h"
#include "../LinkedList.h"
#include "../LinkedListSequence.h"
#include "../ArraySequence.h"
#include "../Sequence.h"
#include <memory>
#include <string>
#include <chrono>
//using namespace std;

struct DynamicArrayTests : public testing::Test {
    size_t size;
    DynamicArray<int>** dc;
    void SetUp() {
        size = 3;
        int a[] {1, 2, 3, 4, 5};
        int b[] {};
        int c[] {1};
        dc = new DynamicArray<int>* [size];
        dc[0] = new DynamicArray<int>(a, 5);
        dc[1] = new DynamicArray<int>(b, 0);
        dc[2] = new DynamicArray<int>(c, 1);

    }
    void TearDown() {
        for (size_t i = 0; i < size; i++) {
            if (dc[i])
                delete dc[i];
        }
        delete [] dc;
    }
};

TEST_F(DynamicArrayTests, DynamicArray_Get2) {
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < dc[k]->GetLength(); ++i) {
            ASSERT_EQ(dc[k]->Get(i), i + 1);
        }
    }
    try {
        dc[1]->Get(0);
    } catch(std::exception& e) {
        ASSERT_STREQ("IndexOutOfRange", e.what());
    }
    try {dc[0]->Get(-1);}
    catch(std::exception& e) {
        ASSERT_STREQ("IndexOutOfRange", e.what());
    }
}
TEST_F(DynamicArrayTests, DynamicArray_and_ICollection) {
    LinkedList<int>* l = new LinkedList<int>(*dc[0]);
    ASSERT_TRUE(*l==*dc[0]);
    delete l;
}
struct DynamicArrayTest : public testing::Test {
    DynamicArray<int> *dc;
    void SetUp() {
        int a[] {1, 2, 3, 4, 5};
        dc = new DynamicArray<int>(a, 5);
    }
    void TearDown() {delete dc;}
};
TEST_F(DynamicArrayTests, DynamicArray_Set) {
    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < dc[k]->GetLength(); ++i) {
            dc[k]->Set(i, i);
        }
    }
    ASSERT_EQ(dc[0]->Get(4), 4);
    ASSERT_EQ(dc[2]->Get(0), 0);
    try {
        dc[1]->Set(0, -1);
    } catch(std::exception& e) {
        ASSERT_STREQ("IndexOutOfRange", e.what());
    }
    try {dc[0]->Set(-1, 3);}
    catch(std::exception& e) {
        ASSERT_STREQ("IndexOutOfRange", e.what());
    }
}
TEST_F(DynamicArrayTests, DynamicArray_Resize) {
    dc[0]->Resize(3);
    dc[2]->Resize(3);
    ASSERT_EQ(dc[0]->GetLength(), 3);
    ASSERT_EQ(dc[2]->GetLength(), 3);
    ASSERT_EQ(dc[0]->Get(0), 1);
    ASSERT_EQ(dc[2]->Get(0), 1);
    std::string str;
    try {
        dc[0]->Get(3);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ("IndexOutOfRange", str.c_str());
    dc[0]->Get(2);
    try {dc[0]->Get(2);}
    catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(DynamicArrayTests, DynamicArray_Enumerator_3) {
    auto e = dc[1]->GetEnumerator();
    int i = 1;
    while (e->next()) {
        ++i;
    }
    ASSERT_EQ(i, 1);
}
TEST_F(DynamicArrayTest, DynamicArray_Get) {
    for (int i = 0; i < dc->GetLength(); ++i) {
        ASSERT_EQ(dc->Get(i), i + 1);
    }
}
TEST_F(DynamicArrayTest, DynamicArray_Enumerator) {
    auto e = dc->GetEnumerator();
    int i = 1;
    while (e->next()) {
        ASSERT_EQ(*(*e), i++);
    }
}
TEST_F(DynamicArrayTest, DynamicArray_Enumerator_2) {
    auto e = dc->GetEnumerator();
    int i = 1;
    while (e->next()) {
        *(*e) = 10;
    }
    e = dc->GetEnumerator();
    while (e->next()) {
        ASSERT_EQ(*(*e), 10);
    }
}
struct LinkedListTests : public testing::Test {
    int size;
    LinkedList<int>** dc;
    LinkedList<int>* dc2;
    LinkedList<int>* dc3;
    void SetUp() {
        size = 4;
        int a[] {1, 2, 3, 4, 5};
        int b[] {1};
        int c[] {};
        int d[] {1, 2, 3, 5, 4};
        dc = new LinkedList<int>* [size];
        dc[0] = new LinkedList<int>(a, 5);
        dc[1] = new LinkedList<int>(b, 1);
        dc[2] = new LinkedList<int>();
        dc[3] = new LinkedList<int>(a, 5);
        dc3 = new LinkedList<int>(b, 1);
        dc2 = new LinkedList<int>(d, 5);
    }
    void TearDown() {
        for (size_t i = 0; i < size; i++) {
            delete dc[i];
        }
        delete dc2;
        delete dc3;
        delete [] dc;
    }
};

TEST_F(LinkedListTests, LinkedList_Get_123) {
    for (int k = 0; k < 2; ++k) {
        for (int i = 0; i < dc[k]->GetLength(); ++i) {
            ASSERT_EQ(dc[k]->Get(i), i + 1);
        }
    }
}

TEST_F(LinkedListTests, LinkedList_Get_edgeCase1) {
    std::string str;
    try {
        dc[2]->Get(0);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_Get_edgeCase2) {
    std::string str;
    try {dc[0]->Get(-1);}
    catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_GetFirst_1) {
    for (int k = 0; k < 2; ++k) {
        ASSERT_EQ(dc[k]->GetFirst(), 1);
    }
}

TEST_F(LinkedListTests, LinkedList_GetFirst_edgeCase1) {
    std::string str;
    try {
        dc[2]->GetFirst();
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_GetFirst_2) {
    ASSERT_EQ(dc2->GetFirst(), 1);
}

TEST_F(LinkedListTests, LinkedList_GetLast_1) {
    for (int k = 0; k < 2; ++k) {
        ASSERT_EQ(dc[k]->GetLast(), dc[k]->GetLength());
    }
}

TEST_F(LinkedListTests, LinkedList_GetLast_edgeCase1) {
    std::string str;
    try {
        dc[2]->GetLast();
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_GetLast_2) {
    ASSERT_EQ(dc[0]->GetLast(), 5);
}
TEST_F(LinkedListTests, LinkedList_Enumerator_3) {
    auto e = dc[1]->GetEnumerator();
    int i = 1;
    while (e->next()) {
        ++i;
    }
    ASSERT_EQ(i, 2);
}
TEST_F(LinkedListTests, LinkedList_Enumerator) {
    auto e = dc[0]->GetEnumerator();
    int i = 1;
    while (e->next()) {
        ASSERT_EQ(*(*e), i++);
    }
}
TEST_F(LinkedListTests, LinkedList_Enumerator4) {
    auto e = dc[2]->GetEnumerator();
    int i = 1;
    while (e->next()) {
        ++i;
    }
    ASSERT_EQ(i, 1);
}
TEST_F(LinkedListTests, LinkedList_Enumerator_2) {
    auto e = dc[0]->GetEnumerator();
    int i = 1;
    while (e->next()) {
        *(*e) = 10;
    }
    e = dc[0]->GetEnumerator();
    while (e->next()) {
        ASSERT_EQ(*(*e), 10);
    }
}

TEST_F(LinkedListTests, LinkedList_Equel) {
    ASSERT_TRUE(*dc[0]==*dc[3]);
    ASSERT_TRUE(*dc[1]==*dc3);
    ASSERT_TRUE(*dc[0]==*dc[0]);
    ASSERT_FALSE(*dc[0]==*dc2);
    ASSERT_TRUE(*dc[2]==LinkedList<int>());
}

TEST_F(LinkedListTests, LinkedList_GetLength_1) {ASSERT_EQ(dc[0]->GetLength(), 5);}
TEST_F(LinkedListTests, LinkedList_GetLength_2) {ASSERT_EQ(dc[1]->GetLength(), 1);}
TEST_F(LinkedListTests, LinkedList_GetLength_3) {ASSERT_EQ(dc[2]->GetLength(), 0);}
TEST_F(LinkedListTests, LinkedList_GetLength_4) {ASSERT_EQ(dc[3]->GetLength(), 5);}
TEST_F(LinkedListTests, LinkedList_GetLength_5) {ASSERT_EQ(dc2->GetLength(), 5);}
TEST_F(LinkedListTests, LinkedList_GetLength_6) {ASSERT_EQ(dc3->GetLength(), 1);}

TEST_F(LinkedListTests, LinkedList_Append_1) {
    int array [] {1,2,3,4,5,6};
    int a = 6;
    dc[0]->Append(a);
    ASSERT_TRUE(*dc[0] == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_Append_2) {
    int array [] {1,2,3};
    dc[1]->Append(2);
    dc[1]->Append(3);
    ASSERT_TRUE(*dc[1] == LinkedList<int>(array, 3));
}
TEST_F(LinkedListTests, LinkedList_Append_edge) {
    dc[2]->Append(1);
    ASSERT_TRUE(*dc[2] == *dc[1]);
}

TEST_F(LinkedListTests, LinkedList_Prepend_1) {
    int array [] {1,2,3,1};
    dc[1]->Prepend(3);
    dc[1]->Prepend(2);
    dc[1]->Prepend(1);
    ASSERT_TRUE(*dc[1] == LinkedList<int>(array, 4));
}
TEST_F(LinkedListTests, LinkedList_Prepend_2) {
    int array [] {0,1,2,3,4,5};
    dc[0]->Prepend(0);
    ASSERT_TRUE(*dc[0] == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_Prepend_edge) {
    int array [] {1,2};
    dc[2]->Prepend(2);
    dc[2]->Prepend(1);
    ASSERT_TRUE(*dc[2] == LinkedList<int>(array, 2));
}
TEST_F(LinkedListTests, LinkedList_Append_Prepend) {
    int array [] {-1,0,1,-1};
    dc[1]->Prepend(0);
    dc[1]->Append(-1);
    dc[1]->Prepend(-1);
    ASSERT_TRUE(*dc[1] == LinkedList<int>(array, 4));
}



TEST_F(LinkedListTests, LinkedList_Set_123) {
    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < dc[k]->GetLength(); ++i) {
            dc[k]->Set(i, i);
        }
    }

    for (int k = 0; k < 3; ++k) {
        for (int i = 0; i < dc[k]->GetLength(); ++i) {
            ASSERT_EQ(dc[k]->Get(i), i);
        }
    }
}

TEST_F(LinkedListTests, LinkedList_Set_edgeCase1) {
    std::string str;
    try {
        dc[2]->Set(0, 1);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_Set_edgeCase2) {
    std::string str;
    try {dc[0]->Set(-1, 0);}
    catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}

TEST_F(LinkedListTests, LinkedList_SetLast_1) {
    for (int k = 0; k < 2; ++k) {
        dc[k]->Set(dc[k]->GetLength()-1, 100);
        ASSERT_EQ(dc[k]->GetLast(), 100);
    }
}
TEST_F(LinkedListTests, LinkedList_GetSubList_1) {
    int array [] {2,3};
    std::unique_ptr<LinkedList<int>> d(dc[0]->GetSubList(1, 3));
    ASSERT_TRUE(*d == LinkedList<int>(array, 2));
}
TEST_F(LinkedListTests, LinkedList_GetSubList_2) {
    int array [] {1};
    std::unique_ptr<LinkedList<int>> d(dc[1]->GetSubList(0, 1));
    ASSERT_TRUE(*d == LinkedList<int>(array, 1));
}
TEST_F(LinkedListTests, LinkedList_GetSubList_3) {
    int array [] {1};
    std::unique_ptr<LinkedList<int>> d(dc2->GetSubList(2, 2));
    ASSERT_TRUE(*d == LinkedList<int>());
}
TEST_F(LinkedListTests, LinkedList_GetSubList_4) {
    int array [] {3, 5, 4};
    std::unique_ptr<LinkedList<int>> d(dc2->GetSubList(2, 5));
    ASSERT_TRUE(*d == LinkedList<int>(array, 3));
}
TEST_F(LinkedListTests, LinkedList_GetSubList_edgeCase1) {
    std::string str;
    try {
        dc[2]->GetSubList(0, 1);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_GetSubList_edgeCase2) {
    std::string str;
    try {
        dc[0]->GetSubList(-1, 1);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_GetSubList_edgeCase3) {
    std::string str;
    try {
        dc[0]->GetSubList(1, 6);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_GetSubList_edgeCase4) {
    std::string str;
    try {
        dc[0]->GetSubList(-1, 15);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_Concat_1) {
    int array [] {1,2,3,4,5,1,2,3,5,4};
    std::shared_ptr<LinkedList<int>> d(dc[0]->Concat(dc2));
    ASSERT_TRUE(*d == LinkedList<int>(array, 10));
}
TEST_F(LinkedListTests, LinkedList_Concat_2) {
    int array [] {1,2,3,4,5,1};
    std::unique_ptr<LinkedList<int>> d(dc[0]->Concat(dc[1]));
    ASSERT_TRUE(*d == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_Concat_3) {
    int array [] {1,1,2,3,4,5};
    std::unique_ptr<LinkedList<int>> d(dc[1]->Concat(dc[0]));
    ASSERT_TRUE(*d == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_Concat_4) {
    int array [] {1,2,3,4,5};
    std::unique_ptr<LinkedList<int>> d(dc[0]->Concat(dc[2]));
    ASSERT_TRUE(*d == LinkedList<int>(array, 5));
}
TEST_F(LinkedListTests, LinkedList_Concat_5) {
    int array [] {1,2,3,4,5};
    std::unique_ptr<LinkedList<int>> d(dc[2]->Concat(dc[0]));
    ASSERT_TRUE(*d == LinkedList<int>(array, 5));
}

TEST_F(LinkedListTests, LinkedList_InsertAt_1) {
    int array [] {1,2,-1,3,4,5};
    dc[0]->InsertAt(-1, 2);
    ASSERT_TRUE(*dc[0] == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_InsertAt_2) {
    int array [] {-1,1,2,3,4,5};
    dc[0]->InsertAt(-1, 0);
    ASSERT_TRUE(*dc[0] == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_InsertAt_3) {
    int array [] {1,2,3,4,5,-1};
    dc[0]->InsertAt(-1, 5);
    ASSERT_TRUE(*dc[0] == LinkedList<int>(array, 6));
}
TEST_F(LinkedListTests, LinkedList_InsertAt_5) {
    int array [] {-1};
    dc[2]->InsertAt(-1, 0);
    ASSERT_TRUE(*dc[2] == LinkedList<int>(array, 1));
}
TEST_F(LinkedListTests, LinkedList_InsertAt_edgeCase_1) {
    std::string str;
    try {
        dc[0]->InsertAt(-1, 6);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_InsertAt_edgeCase_2) {
    std::string str;
    try {
        dc[0]->InsertAt(-1, -1);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
TEST_F(LinkedListTests, LinkedList_InsertAt_edgeCase_3) {
    std::string str;
    try {
        dc[2]->InsertAt(-1, 2);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
struct SequenceTests : public testing::Test {
    int size;
    int blockSize;
    Sequence<int>** dc;
    void SetUp() {
        size = 12;
        blockSize = 6;
        int a[] {1, 2, 3, 4, 5};
        int b[] {1};
        int c[] {};
        int d[] {10, 20, 30};
        dc = new Sequence<int>* [size];
        dc[0] = new LinkedListSequence<int>(a, 5);
        dc[1] = new LinkedListSequence<int>(b, 1);
        dc[2] = new LinkedListSequence<int>();
        dc[3] = new LinkedListSequence<int>(a, 5);
        dc[4] = new LinkedListSequence<int>(b, 1);
        dc[5] = new LinkedListSequence<int>(d, 3);
        dc[6] = new ArraySequence<int>(a, 5);
        dc[7] = new ArraySequence<int>(b, 1);
        dc[8] = new ArraySequence<int>();
        dc[9] = new ArraySequence<int>(a, 5);
        dc[10] = new ArraySequence<int>(b, 1);
        dc[11] = new ArraySequence<int>(d, 3);    }
    void TearDown() {
        for (size_t i = 0; i < size; i++) {
            if (dc[i])
                delete dc[i];
        }
        delete [] dc;
    }
};
int fun1(int x) {
    return x*x;
}
double fun2(int x) {
    return (double)x / 2.0;
}
int fun_sum(int x, int iter) {
    return iter+x;
}
int fun_fibo(int x,int iter) {
    return  2*x + iter;
}
TEST_F(SequenceTests, Sequence_Reduce_1) {
    for (int i = 0; i < size; i += blockSize) {
        int d1 = dc[0+i]->Reduce<int>(&fun_sum, 0);
        ASSERT_EQ(d1, 15);
    }
}
TEST_F(SequenceTests, Sequence_Reduce_2) {
    for (int i = 0; i < size; i += blockSize) {
        int d1 = dc[2+i]->Reduce<int>(&fun_sum, 0);
        ASSERT_EQ(d1, 0);
    }
}
TEST_F(SequenceTests, Sequence_Reduce_3) {
    for (int i = 0; i < size; i += blockSize) {
        int d1 = dc[5+i]->Reduce<int>(&fun_fibo, 0);
        ASSERT_EQ(d1, 120);
    }
}
TEST_F(SequenceTests, Sequence_Map_1) {
    int a [] {1, 2, 3};
    int b [] {1, 4, 9, 16, 25};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->Map<LinkedListSequence<int>,int>(&fun1);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(b, 5));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_Map_2) {
    double b [] {0.5, 1, 1.5, 2, 2.5};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<double> *d1 = dc[0+i]->Map<LinkedListSequence<double>,double>(&fun2);
        ASSERT_TRUE(*d1 == LinkedListSequence<double>(b, 5));
        delete d1;
    }
}

TEST_F(SequenceTests, Sequence_Map_3) {
    double b [] {};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<double> *d1 = dc[2+i]->Map<LinkedListSequence<double>,double>(&fun2);
        ASSERT_TRUE(*d1 == LinkedListSequence<double>());
        delete d1;
    }
}
bool fun_del(int x) {
    return x % 2;
}
bool fun_isEq(int x) {
    return x == 10;
}
TEST_F(SequenceTests, Sequence_Where_1) {
    int a [] {1, 3, 5};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->Where<LinkedListSequence<int>>(&fun_del);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 3));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_Where_2) {
    int a [] {10};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[5+i]->Where<LinkedListSequence<int>>(&fun_isEq);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 1));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_Where_3) {
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->Where<LinkedListSequence<int>>(&fun_isEq);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>());
        delete d1;
    }
}

TEST_F(SequenceTests, LinkedList_Get_1) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[0+i]->Get(2), 3);
    }
}

TEST_F(SequenceTests, LinkedList_Get_2) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[1+i]->Get(0), 1);
    }
}
TEST_F(SequenceTests, Sequence_Get_3) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {dc[2+i]->Get(0);}
        catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Get_edgeCase1) {
    for (int i = 0; i < size; i += blockSize) {
    std::string str;
    try {
        dc[0+i]->Get(5);
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
}
}

TEST_F(SequenceTests, Sequence_Get_edgeCase2) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {dc[0+i]->Get(-1);}
        catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}



TEST_F(SequenceTests, LinkedList_GetFirst_edgeCase1) {
    for (int i = 0; i < size; i += blockSize) {
    std::string str;
    try {
        dc[2+i]->GetFirst();
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}

TEST_F(SequenceTests, LinkedList_GetFirst_2) {
    for (int i = 0; i < size; i += blockSize) {
    ASSERT_EQ(dc[0+i]->GetFirst(), 1);
    }
}

TEST_F(SequenceTests, LinkedList_GetLast_1) {
    for (int k = 0; k < 2; ++k) {
        for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[k+i]->GetLast(), dc[k+i]->GetLength());
        }
    }
}

TEST_F(SequenceTests, LinkedList_GetLast_edgeCase1) {
    for (int i = 0; i < size; i += blockSize) {
    std::string str;
    try {
        dc[2+i]->GetLast();
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Operator_1) {
    for (int i = 0; i < size; i += blockSize) {
    std::string str;
    try {
        (*dc[2+i])[0];
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Operator_2) {
    for (int i = 0; i < size; i += blockSize) {
    std::string str;
    try {
        (*dc[0+i])[-1];
    } catch(std::exception& e) {
        str = e.what();
    }
    ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Operator_3) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            (*dc[0+i])[5];
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Operator_4) {
    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < dc[0+i]->GetLength(); ++j) {
            --(*dc[0+i])[j];
            ASSERT_EQ(dc[0+i]->Get(j), j);
        }
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_00) {
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[2+i]->GetSubsequence(0, 0);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>());
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_0) {
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->GetSubsequence(3, 3);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>());
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_1) {
    int a [] {1, 2, 3};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->GetSubsequence(0, 3);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 3));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_2) {
    int a [] {5};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->GetSubsequence(5, 4);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 1));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_3) {
    int a [] {5};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int> *d1 = dc[0+i]->GetSubsequence(0, 5);
        ASSERT_TRUE(*d1 == *dc[0+i]);
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_4) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            dc[0+i]->GetSubsequence(-1, 6);
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_5) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            dc[0+i]->GetSubsequence(-1, 2);
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_GetSubsequence_6) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            dc[0+i]->GetSubsequence(5, 6);
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_GetLength_1) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[0+i]->GetLength(), 5);
    }
}
TEST_F(SequenceTests, Sequence_GetLength_2) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[1+i]->GetLength(), 1);
    }
}
TEST_F(SequenceTests, Sequence_GetLength_3) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[2+i]->GetLength(), 0);
    }
}
TEST_F(SequenceTests, Sequence_GetLength_4) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[3+i]->GetLength(), 5);
    }
}
TEST_F(SequenceTests, Sequence_GetLength_5) {
    for (int i = 0; i < size; i += blockSize) {
        ASSERT_EQ(dc[4+i]->GetLength(), 1);
    }
}
TEST_F(SequenceTests, Sequence_Append_0) {
    int a [] {10, 20, 30, 4};
    for (int i = 0; i < size; i += blockSize) {
        dc[5+i]->Append(4);
        ASSERT_TRUE(*dc[5+i] == LinkedListSequence<int>(a, 4));
    }
}
TEST_F(SequenceTests, Sequence_Append_1) {
    int a [] {10, 20, 30, 4, 5};
    for (int i = 0; i < size; i += blockSize) {
        dc[5+i]->Append(4);
        dc[5+i]->Append(5);
        ASSERT_TRUE(*dc[5+i] == LinkedListSequence<int>(a, 5));
    }
}
TEST_F(SequenceTests, Sequence_Append_2) {
    int a [] {10};
    for (int i = 0; i < size; i += blockSize) {
        dc[2+i]->Append(10);
        ASSERT_TRUE(*dc[2+i] == LinkedListSequence<int>(a, 1));
    }
}
TEST_F(SequenceTests, DynamicArray_Append) {
    int a [] {10};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        dc[8]->Append(10);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}
TEST_F(SequenceTests, DynamicArray_Prepend) {
    int a [] {10};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        dc[8]->Prepend(10);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}
TEST_F(SequenceTests, Sequence_Prepend_0) {
    int a [] {4,10, 20, 30};
    for (int i = 0; i < size; i += blockSize) {
        dc[5+i]->Prepend(4);
        ASSERT_TRUE(*dc[5+i] == LinkedListSequence<int>(a, 4));
    }
}
TEST_F(SequenceTests, Sequence_Prepend_1) {
    int a [] {5,4,10, 20, 30};
    for (int i = 0; i < size; i += blockSize) {
        dc[5+i]->Prepend(4);
        dc[5+i]->Prepend(5);
        ASSERT_TRUE(*dc[5+i] == LinkedListSequence<int>(a, 5));
    }
}
TEST_F(SequenceTests, Sequence_Prepend_2) {
    int a [] {10};
    for (int i = 0; i < size; i += blockSize) {
        dc[2+i]->Prepend(10);
        ASSERT_TRUE(*dc[2+i] == LinkedListSequence<int>(a, 1));
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_1) {
    int a [] {10};
    for (int i = 0; i < size; i += blockSize) {
        dc[2+i]->InsertAt(10, 0);
        ASSERT_TRUE(*dc[2+i] == LinkedListSequence<int>(a, 1));
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_2) {
    int a [] {10, 1};
    for (int i = 0; i < size; i += blockSize) {
        dc[1+i]->InsertAt(10, 0);
        ASSERT_TRUE(*dc[1+i] == LinkedListSequence<int>(a, 2));
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_3) {
    int a [] {1, 10};
    for (int i = 0; i < size; i += blockSize) {
        dc[1+i]->InsertAt(10, 1);
        ASSERT_TRUE(*dc[1+i] == LinkedListSequence<int>(a, 2));
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_4) {
    int a [] {1,2,10,3,4,5};
    for (int i = 0; i < size; i += blockSize) {
        dc[0+i]->InsertAt(10, 2);
        ASSERT_TRUE(*dc[0+i] == LinkedListSequence<int>(a, 6));
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_6) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            dc[0+i]->InsertAt(10, -1);
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_InsertAt_7) {
    for (int i = 0; i < size; i += blockSize) {
        std::string str;
        try {
            dc[0+i]->InsertAt(10, 6);
        } catch(std::exception& e) {
            str = e.what();
        }
        ASSERT_STREQ(str.c_str(), "IndexOutOfRange");
    }
}
TEST_F(SequenceTests, Sequence_Concat_1) {
    int a [] {1,2,3,4,5,10,20,30};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int>* d1 = dc[0+i]->Concat<LinkedListSequence<int> >(dc[5+i]);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 8));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_Concat_2) {
    int a [] {1,2,3,4,5};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int>* d1 = dc[0+i]->Concat<LinkedListSequence<int> >(dc[2+i]);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 5));
        delete d1;
    }
}
TEST_F(SequenceTests, Sequence_Concat_3) {
    int a [] {10,20,30};
    for (int i = 0; i < size; i += blockSize) {
        Sequence<int>* d1 = dc[2+i]->Concat<LinkedListSequence<int> >(dc[5+i]);
        ASSERT_TRUE(*d1 == LinkedListSequence<int>(a, 3));
        delete d1;
    }
}
#endif
