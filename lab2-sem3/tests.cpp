#include <iostream>
#include <gtest/gtest.h>
#include "all_tests_headers.h"

int main(int argc, char **argv) {
    testsUnique();
    testsShared();
    testsWeak();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
