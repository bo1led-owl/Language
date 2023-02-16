cmake_minimum_required(VERSION 3.15)
project(language)

set(TARGET_NAME main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CXX_COMPILER clang++)

add_subdirectory(src)
