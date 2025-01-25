# stb (project)
cmake_minimum_required(VERSION 3.16)
project(stb)

# c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# stb (target)
add_library(stb STATIC)
# :: files
target_sources(stb PRIVATE stb_image.cc stb_image_write.cc)
# :: include directories
target_include_directories(stb PUBLIC ..)