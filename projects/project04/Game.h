//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "GameUI.h"
#include "GameState.h"
#include "GameLogic.h"
#include <memory>

class Game {
    std::unique_ptr<GameUI> m_UI;
    std::unique_ptr<GameState> m_State;
    std::unique_ptr<GameLogic> m_Logic;

public:
    Game();
    ~Game() = default;

    void exec();

private:
    bool execFrame() const;
    void displayEndGameStatus() const;
};