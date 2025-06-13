cmake_minimum_required(VERSION 3.16)

project(tests)

enable_testing()
add_subdirectory(googletest)
add_executable(test test_main.cpp)
target_link_libraries(test Client model-proto gtest_main)