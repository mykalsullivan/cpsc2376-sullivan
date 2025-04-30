cmake_minimum_required(VERSION 3.25)
project(practice12)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(practice12
	main.cpp
)

target_link_libraries(practice12
	SDL2::SDL2
)
