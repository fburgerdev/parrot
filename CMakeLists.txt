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
# :: assimp (target)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_COMMAND POST_BUILD)
add_subdirectory(vendor/assimp)
target_include_directories(parrot PUBLIC src vendor/assimp/include)
target_include_directories(parrot PUBLIC src ${CMAKE_CURRENT_BINARY_DIR}/vendor/assimp/include)
unset(CMAKE_COMMAND)
unset(BUILD_SHARED_LIBS)
# :: glad (target)
add_subdirectory(vendor/glad)
# :: glfw (target)
set(GLFW_LIBRARY_TYPE STATIC)
add_subdirectory(vendor/glfw)
target_include_directories(parrot PUBLIC src vendor/glfw/include)
unset(GLFW_LIBRARY_TYPE)
# :: json (target)
add_subdirectory(vendor/json)
target_include_directories(parrot PUBLIC vendor/json/include)
# :: stb (target)
add_subdirectory(vendor/stb)

# example_demo (target)
add_executable(example_demo)
# :: files
file(GLOB_RECURSE EXAMPLE_DEMO_SOURCES example/demo/*.hh)
file(GLOB_RECURSE EXAMPLE_DEMO_SOURCES example/demo/*.cc)
target_sources(example_demo PRIVATE ${EXAMPLE_DEMO_SOURCES})
# :: include directories
target_include_directories(example_demo PUBLIC src vendor example/demo)
# :: links
target_link_libraries(example_demo PRIVATE parrot)
target_link_libraries(example_demo PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(example_demo PRIVATE PARROT_GLFW PARROT_OPENGL)

# Optional: Group projects in an IDE
# set_target_properties(parrot PROPERTIES FOLDER Libraries)
# set_target_properties(example_demo PROPERTIES FOLDER Executables)