//
// Created by msullivan on 2/19/25.
//

#include "Quoridor.h"
#include <iostream>
#include <vector>

Quoridor::Quoridor() : m_GameStatus(GameState::NOT_STARTED), m_Player1(-1, -1), m_Player2(-1, -1), m_Turn(false), m_Running(true)
{}

void Quoridor::makeBoard()
{
    // 1. Init board
    m_Board.clear();

    // 2. Init players
    m_Player1.x = 1;
    m_Player1.y = 5;
    m_Player1.walls = 10;
    m_Board.setToken(GameToken::PLAYER_1, 1, 5);

    m_Player2.x = 9;
    m_Player2.y = 5;
    m_Player2.walls = 10;
    m_Board.setToken(GameToken::PLAYER_2, 9, 5);
}

void Quoridor::play()
{
    makeBoard();

    // Main run loop
    bool actionCompleted = true;
    while (m_Running)
    {
        // 1. Print board
        m_Board.printBoard();

        // 2. Current player performs turn

        /* Prompt current player for what they want to do */
        std::cout << "<PLAYER " << std::to_string(m_Turn + 1) << ">\n"
                  << "1: Move\n"
                  << "2: Place wall\n"
                  << "3. Forfeit\n"
                  << "What do you want to do? [1-3]: ";

        int input {-1};
        while (true)
        {
            std::cin >> input;
            if (std::cin.fail() || input < 0 || input > 3)
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid input. Try again. [1-3]: ";
            }
            else break;
        }

        switch (input)
        {
            case 1:
                actionCompleted = move();
            break;
            case 2:
                actionCompleted = placeWall();
            break;
            case 3:
                actionCompleted = forfeit();
            break;
            default:
                break;
        }

        // 3. Check for win condition
        if (actionCompleted)
        {
            checkForWinner();
            if (m_Running) m_Turn = !m_Turn;
        }
    }

    // 3. Display result
    std::string resultMessage;
    switch (m_GameStatus)
    {
        case GameState::PLAYER_1_WINS:
            resultMessage = "Player 1 wins!\n";
            break;
        case GameState::PLAYER_2_WINS:
            resultMessage = "Player 2 wins!\n";
            break;
        case GameState::DRAW:
            resultMessage = "Draw!\n";
            break;
        default:
            resultMessage = "The game ended incorrectly. Fix that.\n";
    }
    std::cout << resultMessage << '\n';
}

bool Quoridor::move()
{
    // Get current player and respective coordinates
    auto &player = (m_Turn == false) ? m_Player1 : m_Player2;
    int newX = player.x;
    int newY = player.y;

    // Display available directions
    std::vector<std::string> directions;
    if (newY > 1 && !detectCollision(newX, newY - 1))  // Check if move up is valid
        directions.emplace_back("Up");
    if (newY < 9 && !detectCollision(newX, newY + 1))  // Check if move down is valid
        directions.emplace_back("Down");
    if (newX > 1 && !detectCollision(newX - 1, newY))  // Check if move left is valid
        directions.emplace_back("Left");
    if (newX < 9 && !detectCollision(newX + 1, newY))  // Check if move right is valid
        directions.emplace_back("Right");

    // If there are no valid directions, return false
    if (directions.empty())
    {
        std::cout << "No valid moves available.\n";
        return false;
    }

    // Display available directions
    std::cout << "Available directions to move:\n";
    for (size_t i = 0; i < directions.size(); ++i)
        std::cout << (i + 1) << ": " << directions.at(i) << "\n";

    // Prompt and retrieve user-chosen direction
    std::cout << "Choose a direction [1-" << directions.size() << "]: ";
    int dirInput;
    while (true)
    {
        std::cin >> dirInput;
        if (std::cin.fail() || dirInput < 1 || dirInput > directions.size())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again. [1-" << directions.size() << "]: ";
        }
        else break;
    }
    const std::string direction = directions.at(dirInput - 1);

    // Update player coordinates based on chosen direction
    if (direction == "Up") newY++;
    else if (direction == "Down") newY--;
    else if (direction == "Left") newX--;
    else if (direction == "Right") newX++;

    // Check if move is valid
    if (!isValidMove(player.x, player.y, newX, newY))
    {
        std::cout << "Invalid move.\n";
        return false;
    }

    // Move player
    m_Board.removeToken(player.x, player.y);
    player.x = newX;
    player.y = newY;
    m_Board.setToken(!m_Turn ? GameToken::PLAYER_1 : GameToken::PLAYER_2, player.x, player.y);
    return true;
}

bool Quoridor::placeWall()
{
    // Display number of current player's walls
    int walls;
    if (m_Turn) walls = m_Player1.walls;
    else walls = m_Player2.walls;

    std::cout << "Walls left: " << walls << '\n';

    // Check if the player has any walls left to use
    if ((m_Turn && m_Player1.walls < 1) || (!m_Turn && m_Player2.walls < 1))
    {
        std::cout << "You are out of walls.\n";
        return false;
    }

    // Prompt the player for wall placement coordinates
    std::cout << "Enter the start (x, y) coordinates for the wall [1-9 1-9]: ";
    int startX, startY;

    while (true)
    {
        std::cin >> startX >> startY;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again. [1-9 1-9]: ";
        }
        else break;
    }

    // Validate if start position is within bounds and not occupied
    if (!Board::isValidPosition(startX, startY))
    {
        std::cout << "Invalid starting position. Try again.\n";
        return false;
    }

    // Display available directions to extend the wall
    std::vector<std::string> directions;
    if (Board::isValidPosition(startX, startY + 1) && !detectCollision(startX, startY + 1)) // Check if up is valid
        directions.emplace_back("Up");
    if (startY < 9 && !detectCollision(startX, startY - 1)) // Check if down is valid
        directions.emplace_back("Down");
    if (startX > 1 && !detectCollision(startX - 1, startY)) // Check if left is valid
        directions.emplace_back("Left");
    if (startX < 9 && !detectCollision(startX + 1, startY)) // Check if right is valid
        directions.emplace_back("Right");

    // If there are no valid positions to extend the wall, return false
    if (directions.empty())
    {
        std::cout << "No available directions to extend the wall.\n";
        return false;
    }

    std::cout << "Available directions to extend the wall:\n";
    for (size_t i = 0; i < directions.size(); ++i)
        std::cout << (i + 1) << ": " << directions.at(i) << "\n";

    // Prompt for direction
    std::cout << "Choose a direction [1-" << directions.size() << "]: ";
    int dirInput;
    while (true)
    {
        std::cin >> dirInput;
        if (std::cin.fail() || dirInput < 1 || dirInput > directions.size())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again. [1-" << directions.size() << "]: ";
        }
        else break;
    }

    // Place the wall in the chosen direction
    const std::string direction = directions.at(dirInput - 1); // Get direction from input
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

    // Decrement the current player's wall counter
    auto& player = (m_Turn == false) ? m_Player1 : m_Player2;
    player.walls--;

    return true;
}

bool Quoridor::forfeit()
{
    std::cout << "Are you sure you want to forfeit? [y/n]: ";

    char input;
    while (true)
    {
        std::cin >> input;
        std::cin.ignore();
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again. [y/n]: ";
            continue;
        }

        if (input == 'y')
        {
            if (m_Turn == false)
            {
                m_GameStatus = GameState::PLAYER_2_WINS;
                m_Running = false;
                return true;
            }
            if (m_Turn == true)
            {
                m_GameStatus = GameState::PLAYER_1_WINS;
                m_Running = false;
                return true;
            }
        }
        else if (input == 'n')
        {
            std::cout << "Aborted.\n";
            return false;
        }
        else
        {
            std::cout << "Invalid input. Try again. [y/n]: ";
        }
    }
}

bool Quoridor::isValidMove(const int oldX, const int oldY, int newX, int newY) const
{
    // Check if new position is out of bounds
    if (!Board::isValidPosition(newX, newY)) return false;

    // Get opponent's position
    const auto &opponent = (m_Turn == false) ? m_Player1 : m_Player2;

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

bool Quoridor::detectCollision(const int x, const int y) const
{
    // Return true if token is not empty or out of bounds
    return (m_Board.getToken(x, y) != GameToken::EMPTY) || !Board::isValidPosition(x, y);
}

bool Quoridor::isValidWallPlacement(const int startX, const int startY, const int endX, const int endY) const
{
    // Check if the wall placement is in bounds
    if (!Board::isValidPosition(startX, startY) || !Board::isValidPosition(endX, endY))
    {
        std::cout << "Wall placement out of bounds.\n";
        return false;
    }

    // Ensure the wall placement is either vertical or horizontal
    if (startX != endX && startY != endY) {
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

    // Check if placing the wall would block the path between players
    if (!isPathAvailable(m_Player1.x, m_Player1.y, m_Player2.x, m_Player2.y))
    {
        std::cout << "Wall placement would block the path between players.\n";
        return false;
    }

    return true;
}

bool Quoridor::isPathAvailable(const int startX, const int startY, const int endX, const int endY) const
{
    if (startX == endX) // Vertical move
    {
        const int minY = (startY < endY) ? startY : endY;
        const int maxY = (startY > endY) ? startY : endY;

        for (int y = minY + 1; y < maxY; ++y)
            if (m_Board.getToken(startX, y) == GameToken::WALL)
                return false;
    }
    else if (startY == endY) // Horizontal move
    {
        const int minX = (startX < endX) ? startX : endX;
        const int maxX = (startX > endX) ? startX : endX;

        for (int x = minX + 1; x < maxX; ++x)
            if (m_Board.getToken(x, startY) == GameToken::WALL)
                return false;
    }

    return true;
}

void Quoridor::checkForWinner()
{
    // Player 1 reaching right-side
    if (m_Turn == false)
    {
        if (m_Player1.x == 9)
        {
            m_GameStatus = GameState::PLAYER_1_WINS;
            m_Running = false;
        }
    }
    // Player 2 reaching left-side
    else if (m_Turn == true)
    {
        if (m_Player2.x == 1)
        {
            m_GameStatus = GameState::PLAYER_2_WINS;
            m_Running = false;
        }
    }
}

