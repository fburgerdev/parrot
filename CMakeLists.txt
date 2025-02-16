# parrot (project)
cmake_minimum_required(VERSION 3.16)
project(parrot)

# c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# parrot (target)
add_library(parrot STATIC)
# :: precompiled headers
target_precompile_headers(parrot PUBLIC src/common.hh)
# :: files
file(GLOB_RECURSE PARROT_SOURCES src/*.hh)
file(GLOB_RECURSE PARROT_SOURCES src/*.cc)
target_sources(parrot PRIVATE ${PARROT_SOURCES})
# :: include directories
target_include_directories(parrot PUBLIC src vendor)
# :: macros
target_compile_definitions(parrot PRIVATE PARROT_GLFW PARROT_OPENGL)

# vendor
# :: download cpm
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.5/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
# :: assimp (target)
CPMAddPackage(
  NAME assimp
  GITHUB_REPOSITORY assimp/assimp
  GIT_TAG v5.4.3
  OPTIONS
    "ASSIMP_INSTALL ON"
    "BUILD_SHARED_LIBS OFF"
    "ASSIMP_BUILD_TESTS OFF"
    "ASSIMP_BUILD_ALL_EXPORTERS_BY_DEFAULT OFF"
    "ASSIMP_BUILD_ASSIMP_VIEW OFF"
)
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/assimp-src/include")
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/assimp-build/include")
# :: glfw (target)
CPMAddPackage(
  NAME glfw
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.4
  OPTIONS
    "GLFW_INSTALL ON"
    "BUILD_SHARED_LIBS OFF"
    "GLFW_BUILD_TESTS OFF"
    "GLFW_BUILD_EXAMPLES OFF"
    "GLFW_BUILD_DOCS OFF"
)
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/glfw-src/include")
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/glfw-build/include")
# :: json (target)
CPMAddPackage(
  NAME json
  VERSION 3.7.3
  URL https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip
  URL_HASH SHA256=87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014
)
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/json-src/include")
target_include_directories(parrot PUBLIC "${CMAKE_BINARY_DIR}/_deps/json-build/include")
# :: glad (target)
add_subdirectory(vendor/glad)
# :: stb (target)
add_subdirectory(vendor/stb)

# example_teapot (target)
add_executable(example_teapot)
# :: files
file(GLOB_RECURSE EXAMPLE_TEAPOT_SOURCES examples/teapot/*.hh)
file(GLOB_RECURSE EXAMPLE_TEAPOT_SOURCES examples/teapot/*.cc)
target_sources(example_teapot PRIVATE ${EXAMPLE_TEAPOT_SOURCES})
# :: include directories
target_include_directories(example_teapot PUBLIC src vendor examples/teapot)
# :: links
target_link_libraries(example_teapot PRIVATE parrot)
target_link_libraries(example_teapot PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(example_teapot PRIVATE PARROT_GLFW PARROT_OPENGL)

# example_pirate (target)
add_executable(example_pirate_bay)
# :: files
file(GLOB_RECURSE EXAMPLE_PIRATE_BAY_SOURCES examples/pirate_bay/*.hh)
file(GLOB_RECURSE EXAMPLE_PIRATE_BAY_SOURCES examples/pirate_bay/*.cc)
target_sources(example_pirate_bay PRIVATE ${EXAMPLE_PIRATE_BAY_SOURCES})
# :: include directories
target_include_directories(example_pirate_bay PUBLIC src vendor examples/pirate_bay)
# :: links
target_link_libraries(example_pirate_bay PRIVATE parrot)
target_link_libraries(example_pirate_bay PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(example_pirate_bay PRIVATE PARROT_GLFW PARROT_OPENGL)

# group projects in an ide
set_target_properties(parrot PROPERTIES FOLDER Parrot)
set_target_properties(example_teapot PROPERTIES FOLDER Examples)
set_target_properties(example_pirate_bay PROPERTIES FOLDER Examples)