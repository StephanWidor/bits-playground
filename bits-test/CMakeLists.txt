cmake_minimum_required(VERSION 3.20)
project(bits-tests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include(GoogleTest)

add_executable(${PROJECT_NAME}
    uint.cpp
    )

target_link_libraries(${PROJECT_NAME}
    bits-lib
    gtest
    gtest_main
    gmock
    gmock_main
    )

gtest_discover_tests(${PROJECT_NAME})
