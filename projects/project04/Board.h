//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "GameToken.h"
#include "WallToken.h"
#include <array>

class Board {
    static constexpr int m_CellsX = 9;
    static constexpr int m_CellsY = 9;
    static constexpr int m_CellSize = 64;
    std::array<std::array<GameToken, m_CellsX>, m_CellsY> m_PlayerGrid {};
    std::array<std::array<WallToken, m_CellsX>, m_CellsY> m_WallGrid {};

    const int m_BoardWidth = m_CellsX * m_CellSize;
    const int m_BoardHeight = m_CellsY * m_CellSize;

public:
    Board();
    ~Board() = default;

    // Cells
    [[nodiscard]] static constexpr int cellsX() { return m_CellsX; }
    [[nodiscard]] static constexpr int cellsY() { return m_CellsY; }

    // Dimensions
    [[nodiscard]] int width() const { return m_BoardWidth; }
    [[nodiscard]] int height() const { return m_BoardHeight; }

    // Player-related
    [[nodiscard]] GameToken getPlayerToken(int x, int y) const;
    bool setPlayerToken(GameToken token, int x, int y);
    bool removePlayerToken(int x, int y);

    // Wall-related
    [[nodiscard]] WallToken getWallToken(int x, int y) const;
    bool setWallToken(WallToken token, int x, int y);
    bool removeWallToken(int x, int y);

    void clear();

    static bool checkBounds(int x, int y);
};