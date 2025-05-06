//
// Created by msullivan on 5/5/25.
//

#pragma once
#include <SDL.h>
#include <string>

class GameWindow {
    SDL_Window* m_Window;
    int m_Width, m_Height;
    std::string m_Title;

public:
    GameWindow(const std::string& title, int width, int height);
    ~GameWindow();

    [[nodiscard]] SDL_Window *window() const { return m_Window; }
    [[nodiscard]] int width() const { return m_Width; }
    [[nodiscard]] int height() const { return m_Height; }
};
