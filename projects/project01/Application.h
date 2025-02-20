//
// Created by msullivan on 2/18/25.
//

#pragma once

class Application {
    bool m_Running;

public:
    Application();
    ~Application();

    int exec();
    void stop();
};