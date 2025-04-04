# my_game (project)
cmake_minimum_required(VERSION 3.16)
project(my_game)

# c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# parrot (target)
# :: cpm
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.5/CPM.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
# :: repo
CPMAddPackage(
  NAME parrot
  GITHUB_REPOSITORY fburgerdev/parrot
  GIT_TAG develop
)

# my_game (target)
add_executable(my_game)
# :: files
file(GLOB_RECURSE MY_GAME_SOURCES src/*.hh)
file(GLOB_RECURSE MY_GAME_SOURCES src/*.cc)
target_sources(my_game PRIVATE ${MY_GAME_SOURCES})
# :: include directories
target_include_directories(my_game PUBLIC src)
# :: links
target_link_libraries(my_game PRIVATE parrot)
target_link_libraries(my_game PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(my_game PRIVATE PARROT_GLFW PARROT_OPENGL)