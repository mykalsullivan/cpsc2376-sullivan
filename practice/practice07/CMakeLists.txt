cmake_minimum_required(VERSION 3.25)
project(practice07)

# Set CMake flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project executable
add_executable(practice07
        main.cpp
        SalariedEmployee.cpp
        HourlyEmployee.cpp
        CommissionEmployee.cpp
)