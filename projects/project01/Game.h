//
// Created by msullivan on 2/18/25.
//

#pragma once

class Game {
    bool m_Running;

public:
    Game();
    ~Game();

    int exec();
    void stop();
};