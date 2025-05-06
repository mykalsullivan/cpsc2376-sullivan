cmake_minimum_required(VERSION 3.25)
project(Quoridor)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

include_directories(
		${SDL2_INCLUDE_DIRS}
		${SDL2_TTF_INCLUDE_DIRS}
		${SDL2_MIXER_INCLUDE_DIRS}
		${SDL2_GFX_INCLUDE_DIR}
)

link_directories(
		${SDL2_LIBRARY_DIRS}
		${SDL2_TTF_LIBRARY_DIRS}
		${SDL2_MIXER_LIBRARY_DIRS}
		${SDL2_GFX_LIBRARY_DIRS}
)

add_executable(Quoridor
		main.cpp
		Game.cpp
		GameLogic.cpp
		GameState.cpp
		Board.cpp
		GameEngine.cpp
		GameWindow.cpp
		GameUI.cpp
)

target_link_libraries(Quoridor
		${SDL2_LIBRARIES}
		${SDL2_TTF_LIBRARIES}
		${SDL2_MIXER_LIBRARIES}
		${SDL2_GFX_LIBRARIES}
)

# Copy the font file into the build directory
file(COPY Ubuntu-Bold.ttf DESTINATION ${CMAKE_BINARY_DIR})