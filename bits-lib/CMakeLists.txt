cmake_minimum_required(VERSION 3.20)

project(bits-lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
    dummy.cpp
    src/sw/bits/uint.h
)

target_include_directories(${PROJECT_NAME} PUBLIC src)
