cmake_minimum_required(VERSION 3.20)

project(HammingCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(lib)
add_subdirectory(bin)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()