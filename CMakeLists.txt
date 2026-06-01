cmake_minimum_required(VERSION 3.16)
project(automotive_misra_demo_simple LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(automotive_misra_demo_simple
    src/main.cpp
    src/brake_demo.cpp
)

target_include_directories(automotive_misra_demo_simple PRIVATE include)
