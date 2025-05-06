//
// Created by msullivan on 5/5/25.
//

#include "GameState.h"

GameState::GameState() : m_Status(Status::NOT_STARTED), m_Turn(false)
{
    m_Board.clear();
    m_Player1 = {0, 4, 10};
    m_Player2 = {8, 4, 10};
    m_Board.setPlayerToken(GameToken::PLAYER_1, 0, 4);
    m_Board.setPlayerToken(GameToken::PLAYER_2, 8, 4);
}

bool GameState::movePlayerTo(Player &player, const int targetX, const int targetY)
{
    // Check if the target position is within bounds
    if (!Board::checkBounds(targetX, targetY))
        return false;

    // Remove the player's old position from the board
    m_Board.removePlayerToken(player.x, player.y);

    // Update the player's position to the new coordinates
    player.x = targetX;
    player.y = targetY;

    // Optionally, update the board with the player's new position
    m_Board.setPlayerToken((m_Turn == false) ? GameToken::PLAYER_1 : GameToken::PLAYER_2, player.x, player.y);

    return true;
}

bool GameState::placeWallAt(const int startX, const int startY, const Direction direction)
{
    // Check if the starting position and all target positions are within bounds
    switch (direction)
    {
        case Direction::UP:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX, startY + 1))
                return false;
            m_Board.setWallToken(WallToken::VERTICAL, startX, startY);
            m_Board.setWallToken(WallToken::VERTICAL, startX, startY + 1);
            break;
        case Direction::DOWN:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX, startY - 1))
                return false;
            m_Board.setWallToken(WallToken::VERTICAL, startX, startY);
            m_Board.setWallToken(WallToken::VERTICAL, startX, startY - 1);
            break;
        case Direction::LEFT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX - 1, startY))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX - 1, startY);
            break;
        case Direction::RIGHT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX + 1, startY))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX + 1, startY);
            break;
        case Direction::UP_LEFT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX - 1, startY + 1))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX - 1, startY + 1);
            break;
        case Direction::UP_RIGHT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX + 1, startY + 1))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX + 1, startY + 1);
            break;
        case Direction::DOWN_LEFT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX - 1, startY - 1))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX - 1, startY - 1);
            break;
        case Direction::DOWN_RIGHT:
            if (!Board::checkBounds(startX, startY) || !Board::checkBounds(startX + 1, startY - 1))
                return false;
            m_Board.setWallToken(WallToken::HORIZONTAL, startX, startY);
            m_Board.setWallToken(WallToken::HORIZONTAL, startX + 1, startY - 1);
            break;
        default:
            return false;
    }

    return true;
}

void GameState::changeStatus(const Status status)
{
    m_Status = status;
}

void GameState::changeTurns()
{
    m_Turn = !m_Turn;
}

Player &GameState::getCurrentPlayer()
{
    return m_Turn ? m_Player2 : m_Player1;
}

Player &GameState::getOpponent()
{
    return m_Turn ? m_Player1 : m_Player2;
}
