cmake_minimum_required(VERSION 3.25)
project(TextBasedVectorOperations)

# Set CMake variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary
add_executable(TextBasedVectorOperations
	main.cpp
)
