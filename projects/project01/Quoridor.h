//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "Board.h"
#include "GameState.h"
#include <string>

struct Player { int x, y, walls; };

class Quoridor {
    Board m_Board;
    GameState m_GameStatus;
    Player m_Player1;
    Player m_Player2;
    bool m_Turn;

public:
    Quoridor();
    ~Quoridor() = default;

    [[nodiscard]] GameState gameStatus() const { return m_GameStatus; }

    // Main game loop
    void play();

private:
    // Sets up the game board
    void makeBoard();

    // Move the current player across the board
    bool move();

    // The current player places a wall on the board
    bool placeWall();

    // Prompts the user to forfeit the game
    bool forfeit();

    // Prints the game rules
    static bool printRules();

    // Checks if a move from a starting coordinate pair to a new one is valid
    [[nodiscard]] bool isValidMove(int oldX, int oldY, int newX, int newY) const;

    // Checks if a cell has collision
    [[nodiscard]] bool detectCollision(int x, int y) const;

    // Checks if the specified coordinates are valid for wall placement
    [[nodiscard]] bool isValidWallPlacement(int startX, int startY, int endX, int endY) const;

    // Checks if a player reaches the other side
    void checkForWinner();

    // Performs a game action based on the input
    bool handleAction(int action);

    // Prompts input from user with bounds checking; returns user value
    [[nodiscard]] static int getNumericInput(const std::string &prompt, int min, int max);

    // Prompts a boolean value from the user; returns true or false based on user input
    [[nodiscard]] static bool getBoolInput(const std::string &prompt);
};