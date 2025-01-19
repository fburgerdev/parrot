# glad (project)
cmake_minimum_required(VERSION 3.16)
project(glad)

# c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# glad (target)
add_library(glad STATIC)
# :: files
target_sources(glad PRIVATE glad.cc)
# :: include directories
target_include_directories(glad PUBLIC ..)