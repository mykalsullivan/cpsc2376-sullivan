//
// Created by msullivan on 2/19/25.
//

#include "Game.h"
#include <iostream>
#include <vector>

Game::Game() : m_GameStatus(Status::NOT_STARTED), m_Player1({-1, -1}), m_Player2({-1, -1}), m_Turn(false)
{
    makeBoard();
}

void Game::makeBoard()
{
    // 1. Init board
    m_Board.clear();

    // 2. Init players
    m_Player1 = {1, 5, 10};
    m_Player2 = {9, 5, 10};

    // 3. Place players on board
    m_Board.setToken(GameToken::PLAYER_1, 1, 5);
    m_Board.setToken(GameToken::PLAYER_2, 9, 5);
}

void Game::display() const
{
    m_Board.printBoard();
}

void Game::exec()
{
    m_GameStatus = Status::ONGOING;
    std::cout << "=== QUORIDOR ===\n";
    printRules();

    // Main run loop
    while (true)
    {
        // 1. Print board
        display();

        // 2. Current player performs turn
        std::string prompt = "<PLAYER " + std::to_string(m_Turn + 1) + ">\n"
                            "1: Move\n"
                            "2: Place wall\n"
                            "3. Forfeit\n"
                            "4. Print rules\n"
                            "What do you want to do?";

        // 3. Check for win condition after action is successfully processed
        if (const int input = getNumericInput(prompt, 1, 4); play(input))
        {
            m_Turn = !m_Turn;
            checkForWinner();
        }

        // 4. Check if the game is still ongoing and exit if it isn't
        if (m_GameStatus != Status::ONGOING) break;
    }
}

bool Game::move()
{
    // Get current player and respective coordinates
    auto &player = (m_Turn == false) ? m_Player1 : m_Player2;
    int newX = player.x;
    int newY = player.y;

    const std::vector<std::string> directions = getAvailableMoveDirections();

    // If there are no valid directions, return false
    if (directions.empty())
    {
        std::cout << "No valid moves available.\n";
        return false;
    }

    const int dirInput = selectFromList("Choose a direction", directions);
    movePlayer(directions.at(dirInput - 1));
    return true;
}

bool Game::placeWall()
{
    // Display number of current player's walls
    const int &walls = (!m_Turn) ? m_Player1.walls : m_Player2.walls;

    std::cout << "Walls left: " << walls << '\n';

    // Check if the player has any walls left to use
    if (walls < 1)
    {
        std::cout << "You are out of walls.\n";
        return false;
    }

    // Prompt the player for wall placement coordinates
    const int startX = getNumericInput("x-coordinate?", 1, 9);
    const int startY = getNumericInput("y-coordinate?", 1, 9);

    // Validate if start position is within bounds and not occupied
    if (!Board::checkBounds(startX, startY))
    {
        std::cout << "Invalid starting position. Try again.\n";
        return false;
    }

    // Display available directions to extend the wall
    const std::vector<std::string> directions = getAvailableWallDirections(startX, startY);

    // If there are no valid positions to extend the wall, return false
    if (directions.empty())
    {
        std::cout << "No available directions to extend the wall.\n";
        return false;
    }

    // Prompt for direction
    const int dirInput = selectFromList("Choose a direction", directions);

    // Place the wall in the chosen direction
    placeWallAt(startX, startY, directions.at(dirInput - 1)); // Get direction from input

    // Decrement the current player's wall counter
    auto& player = (!m_Turn) ? m_Player1 : m_Player2;
    player.walls--;

    return true;
}

bool Game::forfeit()
{
    if (getBoolInput("Are you sure you want to forfeit?"))
    {
        m_GameStatus = m_Turn ? Status::PLAYER_1_WINS : Status::PLAYER_2_WINS;
        return true;
    }
    std::cout << "Aborted.\n";
    return false;
}

bool Game::printRules()
{
    std::cout << "\n=== Rules ===\n"
              << "1. Each player starts on opposite sides of a 9x9 board.\n"
              << "2. On each turn, the current player either moves their pawn, places a wall, forfeits, or displays this menu.\n"
              << "3. Pawns can be moved one cell in any available direction, however they can jump over their opponent if there is not a wall behind them. "
                 "If there is a wall behind the opponent, the pawn can be placed adjacent to it.\n"
              << "4. Speaking of walls, each player gets 10 each."
              << "5. Walls are 2 cells long and can be placed in any available direction. Normally, there would be checking to ensure you don't trap your "
              << "opponent like a jerk, but I was too lazy to implement that here. Just forfeit if you get trapped. Take it like a man.\n"
              << "6. The first player to move their cell to the opposite side wins!\n\n";
    return true;
}


bool Game::isValidMove(const int oldX, const int oldY, int newX, int newY) const
{
    // Check if new position is out of bounds
    if (!Board::checkBounds(newX, newY)) return false;

    // Get opponent's position
    const auto &opponent = (!m_Turn) ? m_Player1 : m_Player2;

    if (abs(newX - oldX) + abs(newY - oldY) == 1)
    {
        if (detectCollision(newX, newY)) return false;

        // Prevent moving into opponent's position unless jumping
        if (newX == opponent.x && newY == opponent.y)
        {
            // Determine jump coordinates (going in the same direction)
            const int jumpX = opponent.x + (opponent.x - oldX);
            const int jumpY = opponent.y + (opponent.y - oldY);

            // Check if we can jump over the opponent
            if (jumpX >= 1 && jumpX <= 9 && jumpY >= 1 && jumpY <= 9 &&
                !detectCollision(jumpX, jumpY))
            {
                // Modify newX and newY to jump instead
                newX = jumpX;
                newY = jumpY;
            }
            else // Side step if jumping straight is blocked
            {
                if (oldX == opponent.x)
                {
                    if (!detectCollision(opponent.x - 1, opponent.y))
                    {
                        newX = opponent.x - 1;
                        newY = opponent.y;
                    }
                    else if (!detectCollision(opponent.x + 1, opponent.y))
                    {
                        newX = opponent.x + 1;
                        newY = opponent.y;
                    }
                    else return false;
                }
                else if (oldY == opponent.y)
                {
                    if (!detectCollision(opponent.x, opponent.y - 1))
                    {
                        newX = opponent.x;
                        newY = opponent.y - 1;
                    }
                    else if (!detectCollision(opponent.x, opponent.y + 1))
                    {
                        newX = opponent.x;
                        newY = opponent.y + 1;
                    }
                    else return false;
                }
            }
        }
    }

    // Check if the final new position is valid
    if (detectCollision(newX, newY)) return false;
    return true;
}

bool Game::detectCollision(const int x, const int y) const
{
    // Return true if token is not empty or out of bounds
    return (m_Board.getToken(x, y) != GameToken::EMPTY) || !Board::checkBounds(x, y);
}

bool Game::isValidWallPlacement(const int startX, const int startY, const int endX, const int endY) const
{
    // Check if the wall placement is in bounds
    if (!Board::checkBounds(startX, startY) || !Board::checkBounds(endX, endY))
    {
        std::cout << "Wall placement out of bounds.\n";
        return false;
    }

    // Ensure the wall placement is either vertical or horizontal
    if (startX != endX && startY != endY)
    {
        std::cout << "Walls must be placed either horizontally or vertically.\n";
        return false;
    }

    // Ensure the wall doesn't overlap with an existing wall or a player token
    for (int x = startX; x <= endX; ++x)
    {
        for (int y = startY; y <= endY; ++y)
        {
            if (m_Board.getToken(x, y) != GameToken::EMPTY)
            {
                std::cout << "You cannot place a wall on an occupied cell.\n";
                return false;
            }
        }
    }

    /* Note: If I was smart enough, I would check to see if a player would be trapped. Since that is too complex for what we are doing currently,
     * I won't implement it here. */
    return true;
}

std::vector<std::string> Game::getAvailableMoveDirections() const
{
    // Get current player and opponent
    const auto &player = (m_Turn == false) ? m_Player1 : m_Player2;
    const auto &opponent = (m_Turn == false) ? m_Player2 : m_Player1;

    const int newX = player.x;
    const int newY = player.y;

    // Display available directions
    std::vector<std::string> directions;
    if (!detectCollision(newX, newY + 1))  // Check if move up is valid
        directions.emplace_back("Up");
    if (!detectCollision(newX, newY - 1))  // Check if move down is valid
        directions.emplace_back("Down");
    if (!detectCollision(newX - 1, newY))  // Check if move left is valid
        directions.emplace_back("Left");
    if (!detectCollision(newX + 1, newY))  // Check if move right is valid
        directions.emplace_back("Right");

    // Check if any direction involves jumping over the current player's opponent
    std::vector<std::string> directionsWithJump;
    if (opponent.x == newX && opponent.y == newY + 1 && !detectCollision(newX, newY + 2))
        directionsWithJump.emplace_back("Up (jump)");
    if (opponent.x == newX && opponent.y == newY - 1 && !detectCollision(newX, newY - 2))
        directionsWithJump.emplace_back("Down (jump)");
    if (opponent.y == newY && opponent.x == newX - 1 && !detectCollision(newX - 2, newY))
        directionsWithJump.emplace_back("Left (jump)");
    if (opponent.y == newY && opponent.x == newX + 1 && !detectCollision(newX + 2, newY))
        directionsWithJump.emplace_back("Right (jump)");

    // Provide diagonal movement options if there is a wall behind the opponent in a direction
    std::vector<std::string> diagonalDirections;
    if (opponent.x == newX && opponent.y == newY - 1) // Opponent is directly above
    {
        if (detectCollision(newX, newY - 2)) // Wall blocking jump
        {
            if (!detectCollision(newX - 1, newY - 1)) diagonalDirections.emplace_back("Left Up (jump)");
            if (!detectCollision(newX + 1, newY - 1)) diagonalDirections.emplace_back("Right Up (jump)");
        }
    }
    else if (opponent.x == newX && opponent.y == newY + 1) // Opponent is directly below
    {
        if (detectCollision(newX, newY + 2)) // Wall blocking jump
        {
            if (!detectCollision(newX - 1, newY + 1)) diagonalDirections.emplace_back("Left Down (jump)");
            if (!detectCollision(newX + 1, newY + 1)) diagonalDirections.emplace_back("Right Down (jump)");
        }
    }
    else if (opponent.y == newY && opponent.x == newX - 1) // Opponent is to the left
    {
        if (detectCollision(newX - 2, newY)) // Wall blocking jump
        {
            if (!detectCollision(newX - 1, newY - 1)) diagonalDirections.emplace_back("Left Up (jump)");
            if (!detectCollision(newX - 1, newY + 1)) diagonalDirections.emplace_back("Left Down (jump)");
        }
    }
    else if (opponent.y == newY && opponent.x == newX + 1) // Opponent is to the right
    {
        if (detectCollision(newX + 2, newY)) // Wall blocking jump
        {
            if (!detectCollision(newX + 1, newY - 1)) diagonalDirections.emplace_back("Right Up (jump)");
            if (!detectCollision(newX + 1, newY + 1)) diagonalDirections.emplace_back("Right Down (jump)");
        }
    }

    // Merge regular directions, jump directions, and diagonal directions
    directions.insert(directions.end(), directionsWithJump.begin(), directionsWithJump.end());
    directions.insert(directions.end(), diagonalDirections.begin(), diagonalDirections.end());

    return directions;
}

std::vector<std::string> Game::getAvailableWallDirections(const int startX, const int startY)
{
    std::vector<std::string> directions;

    // Check each possible direction and validate
    if (Board::checkBounds(startX, startY + 1) && !detectCollision(startX, startY + 1)) // Check if up is valid
        directions.emplace_back("Up");
    if (startY < 9 && !detectCollision(startX, startY - 1)) // Check if down is valid
        directions.emplace_back("Down");
    if (startX > 1 && !detectCollision(startX - 1, startY)) // Check if left is valid
        directions.emplace_back("Left");
    if (startX < 9 && !detectCollision(startX + 1, startY)) // Check if right is valid
        directions.emplace_back("Right");

    return directions;
}

void Game::movePlayer(const std::string& direction)
{
    // Get current player and respective coordinates
    auto &player = (m_Turn == false) ? m_Player1 : m_Player2;
    int newX = player.x;
    int newY = player.y;

    // Update player coordinates based on direction
    if (direction == "Up") newY++;
    else if (direction == "Down") newY--;
    else if (direction == "Left") newX--;
    else if (direction == "Right") newX++;
    else if (direction == "Up (jump)") newY += 2;
    else if (direction == "Down (jump)") newY -= 2;
    else if (direction == "Left (jump)") newX -= 2;
    else if (direction == "Right (jump)") newX += 2;
    else if (direction == "Left Up (jump)") { newX--; newY++; }
    else if (direction == "Right Up (jump)") { newX++; newY++; }
    else if (direction == "Left Down (jump)") { newX--; newY--; }
    else if (direction == "Right Down (jump)") { newX++; newY--; }

    // Check if move is valid
    if (!isValidMove(player.x, player.y, newX, newY))
    {
        std::cout << "Invalid move.\n";
        return; // Early return if move is invalid
    }

    // Move player
    m_Board.removeToken(player.x, player.y);
    player.x = newX;
    player.y = newY;
    m_Board.setToken(!m_Turn ? GameToken::PLAYER_1 : GameToken::PLAYER_2, player.x, player.y);
}

void Game::placeWallAt(const int startX, const int startY, const std::string &direction)
{
    // Place the wall in the chosen direction
    if (direction == "Up")
    {
        m_Board.setToken(GameToken::WALL, startX, startY);
        m_Board.setToken(GameToken::WALL, startX, startY + 1);
    }
    else if (direction == "Down")
    {
        m_Board.setToken(GameToken::WALL, startX, startY);
        m_Board.setToken(GameToken::WALL, startX, startY - 1);
    }
    else if (direction == "Left")
    {
        m_Board.setToken(GameToken::WALL, startX, startY);
        m_Board.setToken(GameToken::WALL, startX - 1, startY);
    }
    else if (direction == "Right")
    {
        m_Board.setToken(GameToken::WALL, startX, startY);
        m_Board.setToken(GameToken::WALL, startX + 1, startY);
    }
}

bool Game::play(const int action)
{
    switch (action)
    {
        case 1: return move();
        case 2: return placeWall();
        case 3: return forfeit();
        case 4: return printRules();
        default: return false;
    }
}

void Game::checkForWinner()
{
    // Player 1 reaching right-side
    if (m_Player1.x == 8)
        m_GameStatus = Status::PLAYER_1_WINS;
    // Player 2 reaching left-side
    if (m_Player2.x == 1)
        m_GameStatus = Status::PLAYER_2_WINS;
}

int Game::getNumericInput(const std::string &prompt, const int min, const int max)
{
    std::cout << prompt << " [" << std::to_string(min) << '-' << std::to_string(max) << "]: ";
    int input;
    while (true)
    {
        std::cin >> input;
        if (!std::cin.fail() && input >= min && input <= max) return input;
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Invalid input. Try again [" << min << "-" << max << "]: ";
    }
}

bool Game::getBoolInput(const std::string &prompt)
{
    std::cout << prompt << " [y/n]: ";
    char input;
    while (true)
    {
        std::cin >> input;
        std::cin.ignore();
        if (!std::cin.fail())
        {
            switch (input)
            {
                case 'y': return true;
                case 'n': return false;
                default: std::cout << "Invalid input. Try again. [y/n]: ";
            }
        }
        else
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again. [y/n]: ";
        }
    }
}

int Game::selectFromList(const std::string &prompt, const std::vector<std::string> &list)
{
    if (list.empty()) return -1;

    std::cout << "Choices:\n";
    for (size_t i {0}; i < list.size(); ++i)
        std::cout << (i + 1) << ": " << list.at(i) << "\n";

    const int listInput = getNumericInput(prompt, 1, static_cast<int>(list.size()));
    return listInput;
}
