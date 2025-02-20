//
// Created by msullivan on 2/19/25.
//

#pragma once
#include "GameToken.h"
#include <array>

class Board {
    std::array<std::array<GameToken, 9>,  9> m_Grid {};

public:
    Board();
    ~Board() = default;

    [[nodiscard]] GameToken getToken(int x, int y) const;
    bool setToken(GameToken token, int x, int y);
    bool removeToken(int x, int y);

    void printBoard() const;
    void clear();
};