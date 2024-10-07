cmake_minimum_required(VERSION 3.5)

project("flatmap_test")

enable_testing()
add_subdirectory(googletest)
add_executable(flatmap_test flatmap_test.cpp flatmap.cpp)
target_compile_options(flatmap_test PRIVATE -Wall -Wextra -std=c++20 -g -O0 -fprofile-arcs -ftest-coverage)
target_link_options(flatmap_test PRIVATE -lgcov --coverage)
target_link_libraries(flatmap_test gtest_main)
