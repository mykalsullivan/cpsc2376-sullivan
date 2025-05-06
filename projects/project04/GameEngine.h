#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <filesystem>

// Forward declaration(s)
class GameWindow;

class GameEngine {
    GameWindow *m_Window;
    SDL_Renderer *m_Renderer;
    TTF_Font *m_Font;
    Mix_Chunk *m_Sound;
    int m_Width;
    int m_Height;


public:
    explicit GameEngine(const std::string& title = "Engine Window",
                        int width = 1280,
                        int height = 960,
                        const std::string &fontPath = std::string(std::filesystem::current_path()) + "/Ubuntu-Bold.ttf",
                        int fontSize = 24,
                        const std::string& soundPath = std::string(std::filesystem::current_path()) + "/move.wav");
    ~GameEngine();

    [[nodiscard]] GameWindow *window() const { return m_Window; }
    [[nodiscard]] SDL_Renderer *renderer() const { return m_Renderer; }
    [[nodiscard]] int width() const { return m_Width; }
    [[nodiscard]] int height() const { return m_Height; }

    void drawCircle(int centerX, int centerY, int radius,
        SDL_Color color = { 255,0,0,255 }) const;

    void clear(SDL_Color color = { 0,0,0,255 }) const;
    void flip() const;

    void drawRectangle(int centerX, int centerY, int rectWidth = 100, int rectHeight = 100,
        SDL_Color color = { 0,0,255,255 }) const;

    void drawText(const std::string& text, int centerX, int centerY,
        SDL_Color color = { 255,255,255,255 }) const;

    void playSound() const;
};
