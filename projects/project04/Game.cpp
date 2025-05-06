//
// Created by msullivan on 2/19/25.
//

#include "Game.h"
#include "GameEngine.h"

Game::Game() :
    m_State(std::make_unique<GameState>()),
    m_Logic(std::make_unique<GameLogic>(m_UI, m_State)),
    m_UI(std::make_unique<GameUI>(m_Logic, m_State))
{}

void Game::exec()
{
    m_State->status() = GameState::Status::ONGOING;
    m_UI->render();
    SDL_Delay(16);

    while (m_State->status() == GameState::Status::ONGOING)
    {
        auto action = m_UI->pollPlayerAction();
        m_UI->render();

        if (action.has_value())
            m_Logic->processTurn(action.value());

        SDL_Delay(16);
    }

    displayEndGameStatus();

    // Prompt to replay
    m_UI->updateStatusMessage("Press 'enter' to play again.", {255, 255, 255, 255});
    m_UI->render();

    bool waitingForReplay = true;
    while (waitingForReplay)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(0);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
            {
                // Only reset the game state
                m_State = std::make_unique<GameState>();
                m_State->status() = GameState::Status::ONGOING;
                m_UI->updateStatusMessage("", {255, 255, 255, 255});
                m_UI->render();
                waitingForReplay = false;
            }
        }
    }

    // Bad practice, but it gets the job done for now.
    exec();
}

bool Game::execFrame() const
{
    m_UI->handleEvents();
    m_UI->handlePlayerInput();
    m_UI->render();
    return m_UI->nextAction() != PlayerAction::NONE;
}

void Game::displayEndGameStatus() const
{
    switch (m_State->status())
    {
        case GameState::Status::PLAYER_1_WINS:
            m_UI->updateStatusMessage("Player 1 wins!", {0, 255, 0, 255});
        break;
        case GameState::Status::PLAYER_2_WINS:
            m_UI->updateStatusMessage("Player 2 wins!", {0, 255, 0, 255});
        break;
        default:
            break;
    }
    m_UI->render();
    SDL_Delay(3000);
}
