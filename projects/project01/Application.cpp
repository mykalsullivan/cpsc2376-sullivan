//
// Created by msullivan on 2/18/25.
//

#include "Application.h"
#include "Quoridor.h"

Application::Application() : m_Running(true)
{

}

Application::~Application()
{

}

int Application::exec()
{
    Quoridor game;
    game.play();
    return 0;
}

void Application::stop()
{
    m_Running = false;
}