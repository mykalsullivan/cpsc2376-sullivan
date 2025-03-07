//
// Created by msullivan on 3/6/25.
//

#include <iostream>

class CalculatorUI {
    bool m_Running {false};

public:
    int run();

private:
    void add()
    {}

    void subtract()
    {}

    void multiply()
    {}

    void divide()
    {}

    void displayAsMixedFraction()
    {}

    void clearFraction()
    {}

    void stop()
    {
        m_Running = false;
    }
};

int main()
{

    return 0;
}