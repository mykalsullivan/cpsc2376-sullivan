cmake_minimum_required(VERSION 3.25)
project(practice05)

# Set CMake flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary for problem 1a
add_executable(problem1a
        problem1a.cpp
)

# Create project binary for problem 2a
add_executable(problem2a
        problem2a.cpp
)

# Create project binary for problem 3a
add_executable(problem3a
        problem3a.cpp
)