//
// Created by msullivan on 5/5/25.
//

#include "GameLogic.h"
#include "GameState.h"
#include "GameUI.h"
#include <cmath>

GameLogic::GameLogic(std::unique_ptr<GameUI> &ui, std::unique_ptr<GameState> &state) :
    m_UI(ui),
    m_State(state)
{}

bool GameLogic::processTurn(const PlayerAction action) const
{
    bool actionSucceeded = false;
    switch (action)
    {
        case PlayerAction::MOVE:
            actionSucceeded = move();
        break;
        case PlayerAction::PLACE_WALL:
            actionSucceeded = placeWall();
        break;
        case PlayerAction::FORFEIT:
            actionSucceeded = forfeit();
        break;
        case PlayerAction::PRINT_RULES:
            actionSucceeded = printRules();
        break;
        default:
            showMessage("Unknown action.");
        return false;
    }

    if (actionSucceeded)
    {
        checkForWinner();
        m_State->changeTurns();
    }
    return actionSucceeded;
}

bool GameLogic::move() const
{
    Player &player = m_State->getCurrentPlayer();
    auto [targetX, targetY] = m_UI->selectedCoordinates();

    if (!Board::checkBounds(targetX, targetY))
    {
        showMessage("Invalid move. Out of bounds.");
        return false;
    }

    if (!isValidMove(player, targetX, targetY))
    {
        showMessage("Invalid move. Try again.");
        return false;
    }

    if (!m_State->movePlayerTo(player, targetX, targetY))
    {
        showMessage("Move failed due to collision or other issues.");
        return false;
    }

    showMessage(std::string("Player moved to (" + std::to_string(targetX) + ", " + std::to_string(targetY) + ")"));
    return true;
}

bool GameLogic::placeWall() const
{
    Player &currentPlayer = m_State->getCurrentPlayer();

    if (currentPlayer.walls < 1)
    {
        showMessage("You are out of walls.");
        return false;
    }

    auto [wallX, wallY] = m_UI->selectedCoordinates();

    if (!Board::checkBounds(wallX, wallY))
    {
        showMessage("Invalid wall position. Out of bounds.");
        return false;
    }

    if (m_State->board().getWallToken(wallX, wallY) != WallToken::NONE)
    {
        showMessage("A wall is already placed there.");
        return false;
    }

    const bool wallPlacementSucceeded = m_State->board().setWallToken(WallToken::HORIZONTAL, wallX, wallY);
    if (!wallPlacementSucceeded)
    {
        showMessage("Failed to place wall. Check position and try again.");
        return false;
    }

    currentPlayer.walls--;
    return true;
}

bool GameLogic::forfeit() const
{
    const Player &currentPlayer = m_State->getCurrentPlayer();
    const Player &player1 = m_State->player1();
    const Player &player2 = m_State->player2();

    if (&currentPlayer == &player1)
    {
        m_State->changeStatus(GameState::Status::PLAYER_2_WINS);
        showMessage("Player 2 wins by forfeit!");
    }
    else if (&currentPlayer == &player2)
    {
        m_State->changeStatus(GameState::Status::PLAYER_1_WINS);
        showMessage("Player 1 wins by forfeit!");
    }

    return true;
}

bool GameLogic::printRules() const
{
    SDL_Rect rulesRect = {50, 50, 700, 500};
    std::string rules =
        "=== Rules ===\n"
        "1. Each player starts on opposite sides of a 9x9 board.\n"
        "2. On each turn, the current player either moves their pawn, places a wall, forfeits, or displays this menu.\n"
        "3. Pawns can be moved one cell in any available direction...\n"
        "4. Each player gets 10 walls.\n"
        "5. Walls are 2 cells long and can be placed in any direction.\n"
        "6. The first player to move their pawn to the opposite side wins!\n";

    TTF_Font *font = TTF_OpenFont("path/to/font.ttf", 24);
    if (!font) return false;

    SDL_Surface *textSurface = TTF_RenderText_Blended(font, rules.c_str(), {255, 255, 255, 255});
    if (!textSurface)
    {
        TTF_CloseFont(font);
        return false;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_UI->engine()->renderer(), textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);

    if (!textTexture) return false;

    SDL_RenderCopy(m_UI->engine()->renderer(), textTexture, nullptr, &rulesRect);
    SDL_DestroyTexture(textTexture);

    return true;
}

bool GameLogic::isValidMove(const Player &player, int newX, int newY) const
{
    const int oldX = player.x;
    const int oldY = player.y;

    if (!Board::checkBounds(newX, newY))
        return false;

    const int dx = newX - oldX;
    const int dy = newY - oldY;

    const auto &opponent = m_State->getOpponent();
    const int oppX = opponent.x;
    const int oppY = opponent.y;

    // 1. Regular adjacent move (orthogonal)
    if ((abs(dx) == 1 && dy == 0) || (abs(dy) == 1 && dx == 0))
        return !detectCollision(newX, newY);

    // 2. Jump over opponent
    if (abs(oppX - oldX) + abs(oppY - oldY) == 1) // opponent adjacent orthogonally
    {
        const int dirX = oppX - oldX;
        const int dirY = oppY - oldY;

        const int jumpX = oppX + dirX;
        const int jumpY = oppY + dirY;

        if (newX == jumpX && newY == jumpY)
        {
            // Try to jump straight over
            if (Board::checkBounds(jumpX, jumpY) && !detectCollision(jumpX, jumpY))
                return true;
        }
        else if (abs(dx) == 1 && abs(dy) == 1)
        {
            // Side-step attempt — check if jump is blocked
            if (!Board::checkBounds(jumpX, jumpY) || detectCollision(jumpX, jumpY))
            {
                // Valid diagonal around opponent if side cell is clear
                if ((newX == oppX - 1 || newX == oppX + 1) && newY == oppY)
                    return !detectCollision(newX, newY);
                if ((newY == oppY - 1 || newY == oppY + 1) && newX == oppX)
                    return !detectCollision(newX, newY);
            }
        }
    }
    return false;
}

bool GameLogic::detectCollision(int x, int y) const
{
    const auto &board = m_State->board();

    // Out of bounds is a collision
    if (!Board::checkBounds(x, y))
        return true;

    // Check if there's a player at the target position
    const auto &p1 = m_State->player1();
    const auto &p2 = m_State->player2();
    if ((p1.x == x && p1.y == y) || (p2.x == x && p2.y == y))
        return true;

    // Check for wall at the target position
    return board.getWallToken(x, y) != WallToken::NONE;
}

std::vector<Direction> GameLogic::getAvailableWallDirections(const int x, const int y) const
{
    std::vector<Direction> directions;
    if (Board::checkBounds(x, y + 1)) directions.push_back(Direction::UP);
    if (Board::checkBounds(x, y - 1)) directions.push_back(Direction::DOWN);
    if (Board::checkBounds(x - 1, y)) directions.push_back(Direction::LEFT);
    if (Board::checkBounds(x + 1, y)) directions.push_back(Direction::RIGHT);
    return directions;
}

void GameLogic::checkForWinner() const
{
    // Player 1 reaching right-side
    if (m_State->player1().x == 8)
        m_State->status() = GameState::Status::PLAYER_1_WINS;
    // Player 2 reaching left-side
    if (m_State->player2().x == 0)
        m_State->status() = GameState::Status::PLAYER_2_WINS;
}

void GameLogic::showMessage(const std::string &message) const
{
    m_UI->updateStatusMessage(message, {255, 0, 0, 0});
}