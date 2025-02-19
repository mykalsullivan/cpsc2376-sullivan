//
// Created by msullivan on 2/18/25.
//

#include "Game.h"

Game::Game() : m_Running(true)
{

}

Game::~Game()
{

}

int Game::exec()
{

    return 0;
}

void Game::stop()
{
    m_Running = false;
}