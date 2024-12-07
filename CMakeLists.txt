cmake_minimum_required(VERSION 3.20)

project(bits-playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Enable building Tests" ON)

add_subdirectory(bits-lib)

if(ENABLE_TESTS)
    add_subdirectory(bits-test)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE bits-lib)
