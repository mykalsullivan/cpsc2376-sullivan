//
// Created by msullivan on 2/19/25.
//

#include "Board.h"
#include <iostream>

Board::Board()
{
    // Initialize grid with empty cells
    clear();
}

GameToken Board::getToken(const int x, const int y) const
{
    const int gridY = 9 - y;
    return m_Grid[gridY][x - 1];
}

bool Board::setToken(const GameToken token, const int x, const int y)
{
    // Return false if out of bounds
    if (y < 0 || y > 9 || x < 0 || x > 9) return false;

    const int gridY = 9 - y;
    m_Grid[gridY][x - 1] = token;
    return true;
}

bool Board::removeToken(const int x, const int y)
{
    // Return false if out of bounds
    if (y < 0 || y > 9 || x < 0 || x > 9) return false;

    const int gridY = 9 - y;
    m_Grid[gridY][x - 1] = GameToken::EMPTY;
    return true;
}

void Board::printBoard() const
{
    // 2. Print y-coordinates and grid
    for (int y = 8; y >= 0; --y)
    {
        std::cout << (y + 1) << " | ";
        for (int x = 0; x < 9; ++x)
        {
            char icon = ' ';
            switch (m_Grid[y][x])
            {
                case GameToken::EMPTY: icon = '.'; break;
                case GameToken::WALL: icon = '#'; break;
                case GameToken::PLAYER_1: icon = '1'; break;
                case GameToken::PLAYER_2: icon = '2'; break;
            }
            std::cout << icon << ' ';
        }
        std::cout << std::endl;
    }

    // 3. Print bottom wall
    std::cout << "    ";
    for (size_t x = 1; x <= 9; ++x) std::cout << x << " ";
    std::cout << std::endl;
}

void Board::clear()
{
    for (auto &row : m_Grid)
        for (auto &token : row)
            token = GameToken::EMPTY;
}