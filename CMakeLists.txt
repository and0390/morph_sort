
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(morph_sort LANGUAGES CXX)

add_subdirectory(tests)
add_subdirectory(benchmarks)