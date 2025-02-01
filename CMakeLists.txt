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

# example_teapot (target)
add_executable(example_teapot)
# :: files
file(GLOB_RECURSE EXAMPLE_TEAPOT_SOURCES example/teapot/*.hh)
file(GLOB_RECURSE EXAMPLE_TEAPOT_SOURCES example/teapot/*.cc)
target_sources(example_teapot PRIVATE ${EXAMPLE_TEAPOT_SOURCES})
# :: include directories
target_include_directories(example_teapot PUBLIC src vendor example/teapot)
# :: links
target_link_libraries(example_teapot PRIVATE parrot)
target_link_libraries(example_teapot PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(example_teapot PRIVATE PARROT_GLFW PARROT_OPENGL)

# example_pirate (target)
add_executable(example_pirate_bay)
# :: files
file(GLOB_RECURSE EXAMPLE_PIRATE_BAY_SOURCES example/pirate_bay/*.hh)
file(GLOB_RECURSE EXAMPLE_PIRATE_BAY_SOURCES example/pirate_bay/*.cc)
target_sources(example_pirate_bay PRIVATE ${EXAMPLE_PIRATE_BAY_SOURCES})
# :: include directories
target_include_directories(example_pirate_bay PUBLIC src vendor example/pirate_bay)
# :: links
target_link_libraries(example_pirate_bay PRIVATE parrot)
target_link_libraries(example_pirate_bay PRIVATE assimp glad glfw stb)
# :: macros
target_compile_definitions(example_pirate_bay PRIVATE PARROT_GLFW PARROT_OPENGL)

# group projects in an ide
set_target_properties(parrot PROPERTIES FOLDER Parrot)
set_target_properties(example_teapot PROPERTIES FOLDER Examples)
set_target_properties(example_pirate_bay PROPERTIES FOLDER Examples)