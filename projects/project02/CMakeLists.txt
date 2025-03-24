cmake_minimum_required(VERSION 3.25)
project(project02)

# Set CMake variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary
add_executable(project02
        main.cpp
        Board.cpp
        Game.h
        Game.cpp
        GameToken.h
)