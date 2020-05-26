cmake_minimum_required(VERSION 3.16)
project(TemplateCpu)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC "-fconcepts")
#target_compile_options(${PROJECT_NAME} PUBLIC "-ftemplate-backtrace-limit=0")
