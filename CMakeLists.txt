cmake_minimum_required(VERSION 3.18)

project(Algorithms)

# Specify output directories.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Build with c++17 support.
set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall \
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded \
        -Wno-switch-enum -Wno-weak-vtables -Wno-exit-time-destructors \
        -Wno-float-equal -Wno-global-constructors"
    )
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_subdirectory("tasks")
add_subdirectory("utils")
