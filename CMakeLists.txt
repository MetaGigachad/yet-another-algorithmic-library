cmake_minimum_required(VERSION 3.24)
project(algorithms_and_data_structures_lib)

set(CMAKE_CXX_STANDARD 20)

add_executable(run-all-tests
        tests/run_all.cpp tests/hash_map.cpp)
