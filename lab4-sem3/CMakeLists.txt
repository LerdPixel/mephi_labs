cmake_minimum_required(VERSION  3.24.1)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()


add_executable(
    my_program.out
    "source/main.cpp"
)

#set(GRAPHVIZ_DIR "/opt/homebrew/Cellar/graphviz/10.0.1")

#file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.dylib")
#target_link_libraries(my_program.out ${GVC_LIBS})
#include_directories("${GRAPHVIZ_DIR}/include")


add_executable(
  test.out
  "source/tests/testsHashTable.cpp"
)
target_link_libraries(
    test.out
    GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(test.out)