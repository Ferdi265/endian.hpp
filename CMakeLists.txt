cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(libendian CXX)

option(LIBENDIAN_DEFAULT_CXXFLAGS "enable default CXXFLAGS" OFF)
option(LIBENDIAN_BUILD_TESTS "build test cases" OFF)
option(LIBENDIAN_BUILD_EXAMPLES "build example binaries" OFF)

if(LIBENDIAN_DEFAULT_CXXFLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(libendian INTERFACE)
target_include_directories(libendian INTERFACE include/)

if(LIBENDIAN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(LIBENDIAN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
