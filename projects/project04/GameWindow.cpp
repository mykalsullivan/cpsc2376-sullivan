//
// Created by msullivan on 5/5/25.
//

#include "GameWindow.h"
#include <string>
#include <stdexcept>

GameWindow::GameWindow(const std::string& title, int width, int height)
    : m_Window(nullptr), m_Width(width), m_Height(height)
{
    m_Window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    if (!m_Window) throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());
}

GameWindow::~GameWindow()
{
    if (m_Window) SDL_DestroyWindow(m_Window);
}