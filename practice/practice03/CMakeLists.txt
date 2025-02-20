cmake_minimum_required(VERSION 3.25)
project(TestStuffIGuess)

# Set CMake variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary
find_package(GTest REQUIRED)
add_executable(practice03
        practice03.cpp
        MathUtils.cpp
        ../../projects/project01/Board.h
        ../../projects/project01/Board.cpp
)

# Enable testing
enable_testing()

# Include test directory
set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ../tests/practice03_test)

# Create test binary
add_executable(practice03_test
        ${CMAKE_INCLUDE_PATH}/practice03_test.cpp
        MathUtils.cpp
)

# Link test executable
target_link_libraries(practice03_test
        GTest::GTest
        GTest::Main
)
