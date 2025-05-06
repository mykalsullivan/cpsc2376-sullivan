//
// Created by msullivan on 2/19/25.
//

#include "Board.h"

Board::Board()
{
    clear();
}

GameToken Board::getPlayerToken(const int x, const int y) const
{
    if (!checkBounds(x, y)) return GameToken::EMPTY; // This may cause issues later
    return m_PlayerGrid.at(y).at(x);
}

bool Board::setPlayerToken(const GameToken token, const int x, const int y)
{
    if (!checkBounds(x, y)) return false;
    m_PlayerGrid.at(y).at(x) = token;
    return true;
}

bool Board::removePlayerToken(const int x, const int y)
{
    if (!checkBounds(x, y)) return false;
    m_PlayerGrid.at(y).at(x) = GameToken::EMPTY;
    return true;
}

WallToken Board::getWallToken(const int x, const int y) const
{
    if (!checkBounds(x, y)) return WallToken::NONE;
    return m_WallGrid.at(y).at(x);
}

bool Board::setWallToken(const WallToken token, const int x, const int y)
{
    if (!checkBounds(x, y)) return false;
    m_WallGrid.at(y).at(x) = token;
    return true;
}

bool Board::removeWallToken(const int x, const int y)
{
    if (!checkBounds(x, y)) return false;
    m_WallGrid.at(y).at(x) = WallToken::NONE;
    return true;
}

void Board::clear()
{
    for (auto &row : m_PlayerGrid)
        for (auto &token : row)
            token = GameToken::EMPTY;

    for (auto &row : m_WallGrid)
        for (auto &token : row)
            token = WallToken::NONE;
}

bool Board::checkBounds(const int x, const int y)
{
    return x >= 0 && x < 9 && y >= 0 && y < 9;
}