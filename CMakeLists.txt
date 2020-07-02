cmake_minimum_required(VERSION 3.10)
project(TemplateCpu)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror -mtune=native -march=native")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif ()

add_executable(${PROJECT_NAME} main.cpp)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # GCC 9 requires another flag for experimental concepts support.
    target_compile_options(${PROJECT_NAME} PUBLIC "-fconcepts")
endif ()

# Change for larger programs, be careful with the maximum depth,
# GCC will need lots of memory, clang will segfault at some point
target_compile_options(${PROJECT_NAME} PUBLIC "-ftemplate-depth=2048")
