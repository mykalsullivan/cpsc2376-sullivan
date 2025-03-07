cmake_minimum_required(VERSION 3.25)
project(practice05)

# Set CMake flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary for problem 1a
add_executable(practice06
        main.cpp
        Fraction.cpp
        MixedFraction.cpp
)