//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "GameToken.h"
#include <array>

class Board {
    std::array<std::array<GameToken, 9>,  9> m_Grid {};

public:
    Board();
    ~Board() = default;

    // Returns the token from the specified coordinates
    [[nodiscard]] GameToken getToken(int x, int y) const;

    // Sets the token at the specified coordinates with the provided token
    bool setToken(GameToken token, int x, int y);

    // Removes the token from a specified cell by replacing it with an empty one
    bool removeToken(int x, int y);

    // Prints the board onto the terminal
    void printBoard() const;

    // Clears the board by filling it with empty cells
    void clear();

    // Checks if the specified cell is out-of-bounds
    static bool checkBounds(int x, int y);
};