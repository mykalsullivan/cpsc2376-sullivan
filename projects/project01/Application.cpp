//
// Created by msullivan on 2/18/25.
//

#include "Application.h"
#include "Quoridor.h"
#include <iostream>

Application::Application() : m_Running(true), m_Player1Wins(0), m_Player2Wins(0), m_GameInstance(nullptr)
{}

int Application::exec()
{
    std::cout << "=== QUORIDOR by M. Sullivan ===\n";
    m_GameInstance = new Quoridor;
    m_GameInstance->play();
    while (true)
    {
        // Update player win counters
        auto lastGameStatus = m_GameInstance->gameStatus();
        if (lastGameStatus == GameState::PLAYER_1_WINS) m_Player1Wins++;
        if (lastGameStatus == GameState::PLAYER_2_WINS) m_Player2Wins++;
        displayResult();

        std::cout << "\nPlayer 1 wins: " << std::to_string(m_Player1Wins) <<
                     "\nPlayer 2 wins: " << std::to_string(m_Player2Wins) <<
                     "\nPlay again? [y/n]: ";
        char input;
        while (true)
        {
            std::cin >> input;
            std::cin.ignore();
            if (!std::cin.fail())
            {
                switch (input)
                {
                    case 'y': reset(); m_GameInstance->play(); break;
                    case 'n': std::cout << "Bye.\n"; stop(); return 0;
                    default: std::cout << "Invalid input. Try again. [y/n]: ";
                }
            }
            else
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid input. Try again. [y/n]: ";
            }
        }
    }
    return 0;
}

void Application::stop()
{
    m_Running = false;
}

void Application::reset()
{
    if (m_GameInstance)
    {
        delete m_GameInstance;
        m_GameInstance = new Quoridor;
    }
}


void Application::displayResult() const
{
    std::string resultMessage;
    switch (m_GameInstance->gameStatus())
    {
        case GameState::NOT_STARTED: resultMessage = "Game not started.\n"; break;
        case GameState::ONGOING: resultMessage = "Game ongoing.\n"; break;
        case GameState::PLAYER_1_WINS: resultMessage = "Player 1 wins!\n"; break;
        case GameState::PLAYER_2_WINS: resultMessage = "Player 2 wins!\n"; break;
        default: resultMessage = "The game ended incorrectly. Fix that.\n";
    }
    std::cout << resultMessage << '\n';
}