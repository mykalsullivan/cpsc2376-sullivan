//
// Created by msullivan on 5/5/25.
//

#pragma once
#include "Player.h"
#include "PlayerAction.h"
#include "Direction.h"
#include <vector>
#include <memory>

// Forward declaration(s)
class GameUI;
class GameState;

class GameLogic {
    std::unique_ptr<GameUI> &m_UI;
    std::unique_ptr<GameState> &m_State;

public:
    GameLogic(std::unique_ptr<GameUI> &ui, std::unique_ptr<GameState> &state);

    bool processTurn(PlayerAction action) const;

    bool move() const;
    bool placeWall() const;
    bool forfeit() const;
    bool printRules() const;

    [[nodiscard]] bool isValidMove(const Player &player, int newX, int newY) const;
    [[nodiscard]] bool detectCollision(int x, int y) const;

    [[nodiscard]] std::vector<Direction> getAvailableWallDirections(int startX, int startY) const;

    void checkForWinner() const;

    void showMessage(const std::string &message) const;
};