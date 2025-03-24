//
// Created by msullivan on 2/18/25.
//

#include "Game.h"
#include <iostream>

void displayGameStatus(const Game::Status &gameStatus)
{
    std::string resultMessage;
    switch (gameStatus)
    {
        case Game::Status::NOT_STARTED: resultMessage = "Game not started.\n"; break;
        case Game::Status::ONGOING: resultMessage = "Game ongoing.\n"; break;
        case Game::Status::PLAYER_1_WINS: resultMessage = "Player 1 wins!\n"; break;
        case Game::Status::PLAYER_2_WINS: resultMessage = "Player 2 wins!\n"; break;
        default: resultMessage = "The game ended incorrectly. Fix that.\n";
    }
    std::cout << resultMessage << '\n';
}

int main()
{
    Game game;
    game.exec();
    displayGameStatus(game.status());
}