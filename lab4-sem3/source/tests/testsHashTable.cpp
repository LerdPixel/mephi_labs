#include <iostream>
#include <gtest/gtest.h>

#include "HashTableTest.h"
#include "GraphTest.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}