//
// Created by msullivan on 2/18/25.
//

#pragma once

// Foward declaration(s)
class Quoridor;

class Application {
    Quoridor *m_GameInstance;
    bool m_Running;
    int m_Player1Wins;
    int m_Player2Wins;

public:
    Application();
    ~Application() = default;

    [[nodiscard]] int exec();
    void stop();

    // Starts a new game
    void reset();

    // Displays result from the last game
    void displayResult() const;
};