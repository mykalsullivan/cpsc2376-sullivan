cmake_minimum_required(VERSION 3.25)
project(practice06)

# Set CMake flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable
add_executable(practice06
        main.cpp
        Fraction.cpp
        MixedFraction.cpp
)