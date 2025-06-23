# CMake Version and project name
cmake_minimum_required(VERSION 3.15)
project(todolist)

# Common Flags
set(COMMON_FLAGS "-g -Wall -pedantic -Wuninitialized -Werror")
set(COMMON_CXX_FLAGS "-std=c++17")

# Apply flags globally
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${COMMON_CXX_FLAGS} ${EXTRA}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${EXTRA}")

# Adds all .cpp files inside the 'src' folder, recursively
file(GLOB_RECURSE SOURCES_BASE CONFIGURE_DEPENDS "src/*.cpp")

# Create executable considering libraries in include (.hpp files)
add_executable(main ${SOURCES_BASE} main/main.cpp)

target_include_directories(main PRIVATE include)