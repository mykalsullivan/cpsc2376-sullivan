cmake_minimum_required(VERSION 3.25)
project(GameProject)

# Set CMake variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary
add_executable(project01
        main.cpp
        Application.cpp
        Board.cpp
        Quoridor.h
        Quoridor.cpp
        GameToken.h
        GameState.h
        ../../practice/practice04/main.cpp
)