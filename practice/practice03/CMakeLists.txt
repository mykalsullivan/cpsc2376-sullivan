cmake_minimum_required(VERSION 3.25)
project(TextBasedVectorOperations)

# Set CMake variables
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create project binary
add_executable(UnitTestingTestIGuess
        practice03.cpp
        MathUtils.cpp
)

# Enable testing
enable_testing()

# Find, create, and link GTest
find_package(GTest REQUIRED)
add_executable(test_UnitTestingTestIGuess
        test_practice03.cpp
        MathUtils.cpp
)

# Link test executable
target_link_libraries(test_UnitTestingTestIGuess
        GTest::GTest
        GTest::Main
)

# Add test target
add_test(NAME MathUtilsTest COMMAND test_UnitTestingTestIGuess)