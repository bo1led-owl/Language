cmake_minimum_required(VERSION 3.15)
project(language)

set(TARGET_NAME compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CXX_COMPILER clang++)

add_subdirectory(src)

string(TOLOWER CMAKE_BUILD_TYPE build_type)
if (build_type STREQUAL debug)
target_compile_options(${TARGET_NAME} PUBLIC -g -Wall -Wextra)
elseif(build_type STREQUAL release)
target_compile_options(${TARGET_NAME} PUBLIC -O2)
endif()
