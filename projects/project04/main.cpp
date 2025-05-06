//
// Created by msullivan on 2/18/25.
//

#include "Game.h"
#include <iostream>

#include "GameState.h"

void displayGameStatus(const GameState::Status &gameStatus)
{
    std::string resultMessage;
    switch (gameStatus)
    {
        case GameState::Status::NOT_STARTED: resultMessage = "Game not started.\n"; break;
        case GameState::Status::ONGOING: resultMessage = "Game ongoing.\n"; break;
        case GameState::Status::PLAYER_1_WINS: resultMessage = "Player 1 wins!\n"; break;
        case GameState::Status::PLAYER_2_WINS: resultMessage = "Player 2 wins!\n"; break;
        default: resultMessage = "The game ended incorrectly. Fix that.\n";
    }
    std::cout << resultMessage << '\n';
}

int main()
{
    Game game;
    game.exec();
}