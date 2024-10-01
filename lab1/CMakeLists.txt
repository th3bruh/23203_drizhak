cmake_minimum_required(VERSION 3.0)

project("flatmap_test")

enable_testing()
add_subdirectory(googletest)
add_executable(flatmap_test flatmap_test.cpp)
target_compile_options(flatmap_test PRIVATE -fprofile-arcs -ftest-coverage)
target_link_options(flatmap_test PRIVATE -lgcov --coverage)
target_link_libraries(flatmap_test gtest_main)
