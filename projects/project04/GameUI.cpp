//
// Created by msullivan on 5/5/25.
//

#include "GameUI.h"
#include "GameEngine.h"
#include "GameWindow.h"
#include "GameState.h"
#include <iostream>
#include <algorithm>

GameUI::GameUI(std::unique_ptr<GameLogic> &logic,
               std::unique_ptr<GameState> &state)
                : m_Engine(std::make_unique<GameEngine>()),
                  m_Logic(logic),
                  m_State(state),
                  m_SelectedCoords({-1, -1})
{}

void GameUI::handlePlayerInput()
{
    if (m_NextAction == PlayerAction::NONE) return;

    // Forward the action to GameLogic
    bool actionSucceeded = false;
    switch (m_NextAction)
    {
        case PlayerAction::MOVE:
        case PlayerAction::PLACE_WALL:
        case PlayerAction::FORFEIT:
            actionSucceeded = m_Logic->processTurn(m_NextAction); // Use GameLogic's processTurn
        break;
        default:
            break;
    }

    // Reset after processing
    if (actionSucceeded)
        m_NextAction = PlayerAction::NONE;
    else {}
        // Handle failure (you can show an error or handle it accordingly)
}

std::optional<PlayerAction> GameUI::pollPlayerAction()
{
    handleEvents();
    handlePlayerInput();

    if (m_NextAction != PlayerAction::NONE)
    {
        PlayerAction action = m_NextAction;
        m_NextAction = PlayerAction::NONE;
        return action;
    }
    return std::nullopt;
}

void GameUI::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            exit(0);

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            const int offsetX = (m_Engine->window()->width() - (64 * 9)) / 2;
            const int offsetY = (m_Engine->window()->height() - (64 * 9)) / 2;
            int boardX = (event.button.x - offsetX) / 64;
            int boardY = (event.button.y - offsetY) / 64;

            boardX = std::clamp(boardX, 0, 8);
            boardY = std::clamp(boardY, 0, 8);

            if (boardX >= 0 && boardX <= 8 && boardY >= 0 && boardY <= 8)
            {
                m_SelectedCoords = {boardX, boardY};
                std::cout << "Mouse click mapped to: (" << boardX << ", " << boardY << ")\n";
                m_NextAction = PlayerAction::MOVE;
            }
            else
            {
                std::cout << "Click out of bounds: (" << boardX << ", " << boardY << ")\n";
                m_NextAction = PlayerAction::NONE;
            }
        }

        if (event.type == SDL_KEYDOWN)
        {
            bool jumpHeld = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_J];
            int x = m_State->getCurrentPlayer().x;
            int y = m_State->getCurrentPlayer().y;

            int jump = jumpHeld ? 2 : 1;

            switch (event.key.keysym.sym)
            {
                case SDLK_f:
                    m_NextAction = PlayerAction::FORFEIT;
                break;
                case SDLK_r:
                    m_NextAction = PlayerAction::PRINT_RULES;
                break;
                case SDLK_UP:
                    if (y >= jump)
                        m_SelectedCoords = {x, y - jump};
                m_NextAction = PlayerAction::MOVE;
                break;
                case SDLK_DOWN:
                    if (y + jump <= 8)
                        m_SelectedCoords = {x, y + jump};
                m_NextAction = PlayerAction::MOVE;
                break;
                case SDLK_LEFT:
                    if (x >= jump)
                        m_SelectedCoords = {x - jump, y};
                m_NextAction = PlayerAction::MOVE;
                break;
                case SDLK_RIGHT:
                    if (x + jump <= 8)
                        m_SelectedCoords = {x + jump, y};
                m_NextAction = PlayerAction::MOVE;
                break;
                default:
                    break;
            }
        }
    }
}

PlayerAction GameUI::nextAction()
{
    const PlayerAction action = m_NextAction;
    m_NextAction = PlayerAction::NONE;
    return action;
}

std::pair<int, int> GameUI::selectedCoordinates()
{
    m_CoordSelected = false;
    return m_SelectedCoords;
}

void GameUI::updateStatusMessage(const std::string &text, SDL_Color color)
{
    m_StatusMessage = text;
    m_StatusColor = color;
}

void GameUI::drawWalls() const
{
    // Loop through all the cells in the board
    for (int x = 0; x < 9; ++x)
    {
        for (int y = 0; y < 9; ++y)
        {
            // Check if there's a wall at the current position
            if (m_State->board().getWallToken(x, y) != WallToken::NONE)
            {
                // Check if the wall is placed horizontally or vertically
                const bool isVerticalWall = (m_State->board().getWallToken(x, y) == WallToken::VERTICAL);

                // Get the board offset to adjust for wall position
                constexpr int cellSize = 64;
                constexpr int boardSize = 9;
                const int offsetX = (m_Engine->window()->width() - (cellSize * boardSize)) / 2;
                const int offsetY = (m_Engine->window()->height() - (cellSize * boardSize)) / 2;

                // Draw a wall at this position
                SDL_SetRenderDrawColor(m_Engine->renderer(), 255, 255, 0, 255); // Yellow color for walls
                SDL_Rect wallRect;

                if (isVerticalWall)
                    wallRect = {offsetX + x * cellSize + 25, offsetY + y * cellSize + 25, 50, 100}; // Vertical wall
                else
                    wallRect = {offsetX + x * cellSize + 25, offsetY + y * cellSize + 25, 100, 50}; // Horizontal wall

                SDL_RenderFillRect(m_Engine->renderer(), &wallRect);
            }
        }
    }
}

void GameUI::drawBoardGrid() const
{
    constexpr int cellSize = 64;
    constexpr int boardSize = 9;
    constexpr int boardWidth = cellSize * boardSize;
    constexpr int boardHeight = cellSize * boardSize;

    // Center the board in the window
    const int offsetX = (m_Engine->window()->width() - boardWidth) / 2;
    const int offsetY = (m_Engine->window()->height() - boardHeight) / 2;

    SDL_SetRenderDrawColor(m_Engine->renderer(), 200, 200, 200, 255);
    for (int i = 0; i <= boardSize; ++i)
    {
        int x = offsetX + i * cellSize;
        SDL_RenderDrawLine(m_Engine->renderer(), x, offsetY, x, offsetY + boardHeight);  // Vertical lines
        int y = offsetY + i * cellSize;
        SDL_RenderDrawLine(m_Engine->renderer(), offsetX, y, offsetX + boardWidth, y);  // Horizontal lines
    }
}

void GameUI::drawPlayers() const
{
    constexpr int playerSize = 24; // Adjust size as needed

    // Get Player 1 and Player 2 positions
    const int player1X = m_State->player1().x;
    const int player1Y = m_State->player1().y;
    const int player2X = m_State->player2().x;
    const int player2Y = m_State->player2().y;

    const int offsetX = (m_Engine->width() - m_State->board().width()) / 2;
    const int offsetY = (m_Engine->height() - m_State->board().height()) / 2;

    // Player 1 (Blue)
    SDL_Color player1Color = { 0, 0, 255, 255 };  // Blue
    SDL_Rect player1Rect = {
        offsetX + player1X * 64 + (64 - playerSize) / 2,
        offsetY + player1Y * 64 + (64 - playerSize) / 2,
        playerSize,
        playerSize
    };

    SDL_SetRenderDrawColor(m_Engine->renderer(), player1Color.r, player1Color.g, player1Color.b, player1Color.a);
    SDL_RenderFillRect(m_Engine->renderer(), &player1Rect);

    // Player 2 (Red)
    SDL_Color player2Color = { 255, 0, 0, 255 };  // Red
    SDL_Rect player2Rect = {
        offsetX + player2X * 64 + (64 - playerSize) / 2,
        offsetY + player2Y * 64 + (64 - playerSize) / 2,
        playerSize,
        playerSize
    };

    SDL_SetRenderDrawColor(m_Engine->renderer(), player2Color.r, player2Color.g, player2Color.b, player2Color.a);
    SDL_RenderFillRect(m_Engine->renderer(), &player2Rect);
}

void GameUI::drawBoard() const
{
    drawBoardGrid();
    drawPlayers();
    drawWalls();
}

void GameUI::drawStatusMessage() const
{
    const int x = 10;
    const int y = m_Engine->window()->height() - 30;
    m_Engine->drawText(m_StatusMessage, x, y, m_StatusColor);
}

void GameUI::drawTurnInfo() const
{
    const std::string turnText = "Player " + std::to_string(m_State->turn() + 1) + "'s Turn";
    const SDL_Color white = {255, 255, 255, 255};

    // Render turn info at top center
    const int textX = (m_Engine->window()->width() / 2) - 80;
    const int textY = 10;
    m_Engine->drawText(turnText, textX, textY, white);

    // Player 1 wall count (left side)
    const int p1Walls = m_State->player1().walls;
    const std::string p1Text = "Walls: " + std::to_string(p1Walls);
    m_Engine->drawText(p1Text, 10, 10, white);

    // Player 2 wall count (right side)
    const int p2Walls = m_State->player2().walls;
    const std::string p2Text = "Walls: " + std::to_string(p2Walls);
    const int p2TextX = m_Engine->window()->width() - 120; // Adjust based on font size
    m_Engine->drawText(p2Text, p2TextX, 10, white);
}

void GameUI::drawDebugInfo() const
{
    const auto &p1 = m_State->player1();
    const auto &p2 = m_State->player2();

    const std::string p1PosText = "P1 pos: (" + std::to_string(p1.x) + ", " + std::to_string(p1.y) + ")";
    const std::string p2PosText = "P2 pos: (" + std::to_string(p2.x) + ", " + std::to_string(p2.y) + ")";

    constexpr SDL_Color white = {255, 255, 255, 255};

    // Print player positions on the window (bottom left corner)
    m_Engine->drawText(p1PosText, 20, m_Engine->window()->height() - 130, white);
    m_Engine->drawText(p2PosText, 20, m_Engine->window()->height() - 100, white);
}

void GameUI::drawUI() const
{
    drawStatusMessage();
    drawTurnInfo();
    drawDebugInfo();
}

void GameUI::clear() const
{
    SDL_SetRenderDrawColor(m_Engine->renderer(), 0, 0, 0, 255);
    SDL_RenderClear(m_Engine->renderer());
}

void GameUI::render() const
{
    clear();
    drawBoard();
    drawUI();
    SDL_RenderPresent(m_Engine->renderer());
}
