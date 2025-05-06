//
// Created by msullivan on 5/5/25.
//

#pragma once
#include "Board.h"
#include "Player.h"
#include "Direction.h"

class GameState {
public:
    enum class Status {
        NOT_STARTED,
        ONGOING,
        PLAYER_1_WINS,
        PLAYER_2_WINS
    };

private:
    Board m_Board;
    Player m_Player1;
    Player m_Player2;
    Status m_Status;
    bool m_Turn;

public:
    GameState();
    ~GameState() = default;

    Board &board() { return m_Board; }
    Player &player1() { return m_Player1; }
    Player &player2() { return m_Player2; }
    Status &status() { return m_Status; }
    [[nodiscard]] bool turn() const { return m_Turn; }

    bool movePlayerTo(Player &player, int targetX, int targetY);
    bool placeWallAt(int startX, int startY, Direction direction);

    void changeStatus(Status status);
    void changeTurns();

    Player &getCurrentPlayer();
    Player &getOpponent();
};