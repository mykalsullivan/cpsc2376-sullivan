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
    // Return a wall if invalid. This may cause bugs, but oh well.
    if (!isValidPosition(x, y)) return GameToken::WALL;
    return m_Grid.at(y - 1).at(x - 1);
}

bool Board::setToken(const GameToken token, const int x, const int y)
{
    // Return false if out of bounds
    if (!isValidPosition(x, y)) return false;

    m_Grid.at(y - 1).at(x - 1) = token;
    return true;
}

bool Board::removeToken(const int x, const int y)
{
    // Return false if out of bounds
    if (!isValidPosition(x, y)) return false;

    m_Grid.at(y - 1).at(x - 1) = GameToken();
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

bool Board::isValidPosition(const int x, const int y)
{
    // Out of bounds
    return (!(x < 1 || x > 9 || y < 1 || y > 9));
}