cmake_minimum_required(VERSION 3.10)
project(lab4)

include_directories(includes)

add_executable(csv src/csv.cpp)
add_executable(FlatMap src/FlatMap.cpp)
add_executable(tuple src/tuple.cpp)
