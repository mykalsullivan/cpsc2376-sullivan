#include "GameEngine.h"
#include "GameWindow.h"
#include <iostream>
#include <stdexcept>

GameEngine::GameEngine(const std::string& title, const int width, const int height,
    const std::string &fontPath, const int fontSize, const std::string& soundPath)
    : m_Window(nullptr),
        m_Renderer(nullptr),
        m_Font(nullptr),
        m_Sound(nullptr),
        m_Width(width),
        m_Height(height)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL failed to initialize. SDL_Error: "
            << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL_Init failed");
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF failed to initialize. TTF_Error: "
            << TTF_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("TTF_Init failed");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer failed to initialize. Mix_Error: "
            << Mix_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("Mix_OpenAudio failed");
    }

    m_Window = new GameWindow(title, width, height);
    if (!m_Window)
    {
        std::cerr << "Window could not be created. SDL_Error: "
            << SDL_GetError() << std::endl;
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("SDL_Createm_Window failed");
    }

    m_Renderer = SDL_CreateRenderer(m_Window->window(), -1, SDL_RENDERER_ACCELERATED);
    if (!m_Renderer)
    {
        std::cerr << "Renderer failed to initialize. SDL_Error: "
            << SDL_GetError() << std::endl;
        if (m_Window) delete m_Window;
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("SDL_Createm_Renderer failed");
    }

    m_Font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!m_Font)
    {
        std::cerr << "Failed to load font. TTF_Error: "
            << TTF_GetError() << std::endl;
        if (m_Window) delete m_Window;
        SDL_DestroyRenderer(m_Renderer);
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
        throw std::runtime_error("TTF_OpenFont failed");
    }

    m_Sound = Mix_LoadWAV(soundPath.c_str());
    if (!m_Sound)
    {
        std::cerr << "Failed to load sound. Mix_Error: "
            << Mix_GetError() << std::endl;
        // Do not throw, continue without m_Sound.
    }
}

GameEngine::~GameEngine()
{
    if (m_Sound) Mix_FreeChunk(m_Sound);
    if (m_Font) TTF_CloseFont(m_Font);
    if (m_Renderer) SDL_DestroyRenderer(m_Renderer);
    if (m_Window) delete m_Window;
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void GameEngine::drawCircle(const int centerX, const int centerY, const int radius, const SDL_Color color) const
{
    filledCircleRGBA(m_Renderer, centerX, centerY, radius, color.r, color.g, color.b, color.a);
    aacircleRGBA(m_Renderer, centerX, centerY, radius, color.r, color.g, color.b, color.a);
}

void GameEngine::drawRectangle(int centerX, int centerY, int rectWidth, int rectHeight, SDL_Color color) const
{
    SDL_Rect rect;
    rect.x = centerX - rectWidth / 2;
    rect.y = centerY - rectHeight / 2;
    rect.w = rectWidth;
    rect.h = rectHeight;

    SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_Renderer, &rect);
}

void GameEngine::drawText(const std::string& text, const int centerX, const int centerY, const SDL_Color color) const
{
    // Don't render empty text
    if (text.empty()) return;

    SDL_Surface *textSurface = TTF_RenderText_Blended(m_Font, text.c_str(), color);
    if (!textSurface)
    {
        std::cerr << "Unable to render text surface. TTF_Error: "
                  << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_Renderer, textSurface);
    if (!textTexture)
    {
        std::cerr << "Unable to create texture from rendered text. SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect destRect;
    destRect.w = textSurface->w;
    destRect.h = textSurface->h;
    destRect.x = centerX;  // Position relative to the top-left corner
    destRect.y = centerY;  // Position relative to the top-left corner

    SDL_RenderCopy(m_Renderer, textTexture, nullptr, &destRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void GameEngine::clear(const SDL_Color color) const
{
    // Clear screen (set background to black).
    SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(m_Renderer);
}
void GameEngine::flip() const
{
    SDL_RenderPresent(renderer());
}

void GameEngine::playSound() const
{
    if (m_Sound) Mix_PlayChannel( - 1, m_Sound, 0);
}

