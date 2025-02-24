//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "Board.h"
#include "GameState.h"

struct Player {
    int x, y;
    int walls;
};

class Quoridor {
    Board m_Board;
    GameState m_GameStatus;
    Player m_Player1;
    Player m_Player2;
    bool m_Turn;
    bool m_Running;

public:
    Quoridor();
    ~Quoridor() = default;

    [[nodiscard]] GameState gameStatus() const { return m_GameStatus; }
    void makeBoard();
    void play();

private:
    bool move();
    bool placeWall();
    bool forfeit();

    bool isValidMove(int oldX, int oldY, int newX, int newY) const;
    bool detectCollision(int x, int y) const;

    bool isValidWallPlacement(int startX, int startY, int endX, int endY) const;
    bool isPathAvailable(int startX, int startY, int endX, int endY) const;

    void checkForWinner();
};