//
// Created by msullivan on 5/5/25.
//

#pragma once
#include "GameEngine.h"
#include "GameLogic.h"
#include "GameState.h"
#include "Direction.h"
#include "Player.h"
#include "PlayerAction.h"
#include <string>
#include <utility>
#include <memory>
#include <optional>

class GameUI {
    std::unique_ptr<GameEngine> m_Engine;
    std::unique_ptr<GameLogic> &m_Logic;
    std::unique_ptr<GameState> &m_State;

    std::string m_StatusMessage;
    SDL_Color m_StatusColor {};
    PlayerAction m_NextAction = PlayerAction::NONE;

    bool m_CoordSelected = false;
    std::pair<int, int> m_SelectedCoords;
    Direction m_SelectedDirection = Direction::NONE;

public:
    GameUI(std::unique_ptr<GameLogic> &logic,
            std::unique_ptr<GameState> &state);
    ~GameUI() = default;

    [[nodiscard]] std::unique_ptr<GameEngine> &engine() { return m_Engine; }
    [[nodiscard]] std::string statusMessage() const { return m_StatusMessage; }

    void handlePlayerInput();
    std::optional<PlayerAction> pollPlayerAction();
    void processPlayerAction(Player &player);
    void handleEvents();
    void updateStatusMessage(const std::string &text, SDL_Color color);

    void drawBoardGrid() const;
    void drawPlayer(int x, int y, int offsetX, int offsetY) const;
    void drawPlayers() const;
    void drawWalls() const;
    void drawBoard() const;

    void drawStatusMessage() const;
    void drawTurnInfo() const;
    void drawDebugInfo() const;
    void drawUI() const;

    void clear() const;
    void render() const;

    PlayerAction nextAction();
    std::pair<int, int> selectedCoordinates();
};