//
// Created by msullivan on 2/26/25.
//

#include <algorithm>

#include "Input.h"
#include <iostream>
#include <numeric>
#include <list>

class Application {
    bool m_Running {false};
    std::list<int> m_Ints {};

public:
    Application() = default;
    ~Application() = default;

    int exec()
    {
        std::cout << "Algorithms (std::accumulate) by M. Sullivan\n";

        gatherIntegers();
        printEachElementSquared();
        sumAllSquaredValuesAndPrintResult();

        return 0;
    }

private:
    void gatherIntegers()
    {
        const std::string prompt = "Enter a number (0 when finished)";
        int input {};

        do
        {
            input = Input::numberPrompt(prompt, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);
            m_Ints.emplace_back(input);
        } while (input != 0);
    }

    void printEachElementSquared()
    {
        int i {0};
        std::for_each(m_Ints.begin(), m_Ints.end(), [&i](int &value)
        {
            value *= value;
            std::cout << '#' << ++i << " squared: " << value << '\n';
        });
    }

    void sumAllSquaredValuesAndPrintResult()
    {
        const int squaredValuesSum = std::accumulate(m_Ints.begin(), m_Ints.end(), 0, [](const int total, const int num)
        {
            return total + num;
        });
        std::cout << "Sum of squared list elements: " << squaredValuesSum << '\n';
    }

    void stop()
    {
        m_Running = false;
    }
};

int main()
{
    Application app;
    return app.exec();
}