cmake_minimum_required(VERSION 3.16)
project(core)

set(CMAKE_CXX_STANDARD 17)

add_library(core SHARED src/thread_pool.cpp include/thread_pool.h)
add_library(core SHARED src/map_generator.cpp include/map_generator.h)
