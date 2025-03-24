//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "Board.h"
#include <string>
#include <vector>

struct Player { int x, y, walls; };

class Game {
public:
    enum class Status {
        NOT_STARTED,
        ONGOING,
        PLAYER_1_WINS,
        PLAYER_2_WINS
    };

private:
    Board m_Board;
    Status m_GameStatus;
    Player m_Player1;
    Player m_Player2;
    bool m_Turn;

public:
    Game();
    ~Game() = default;

    [[nodiscard]] Status status() const { return m_GameStatus; }

    // Main game loop
    void exec();

    // Return

private:
    // Sets up the game board
    void makeBoard();

    // Displays game board
    void display() const;

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

    // Checks for available places to move
    [[nodiscard]] std::vector<std::string> getAvailableMoveDirections() const;

    // Checks for available directions to place a wall
    [[nodiscard]] std::vector<std::string> getAvailableWallDirections(int startX, int startY);

    // Moves player to a specified cell on the board
    void movePlayer(const std::string &direction);

    // Places a wall at a specified location on the board
    void placeWallAt(int startX, int startY, const std::string &direction);

    // Performs a game action based on the input
    bool play(int action);

    // Checks if a player reaches the other side
    void checkForWinner();

    // Prompts input from user with bounds checking; returns user value
    [[nodiscard]] static int getNumericInput(const std::string &prompt, int min, int max);

    // Prompts a boolean value from the user; returns true or false based on user input
    [[nodiscard]] static bool getBoolInput(const std::string &prompt);

    // Allows the user to select from a list
    [[nodiscard]] static int selectFromList(const std::string &prompt, const std::vector<std::string> &list);
};