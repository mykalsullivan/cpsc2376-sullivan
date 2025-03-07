//
// Created by msullivan on 2/26/25.
//

#include "Input.h"
#include <iostream>
#include <numeric>
#include <vector>

class Application {
    bool m_Running {false};
    std::vector<int> m_Ints {};

public:
    Application() = default;
    ~Application() = default;

    int exec()
    {
        std::cout << "Algorithms (std::accumulate) by M. Sullivan\n";

        gatherIntegers();
        calculateSumOfVectorElements();
        calculateProductOfAllVectorElements();

        return 0;
    }

private:
    void gatherIntegers()
    {
        for (int i {0}; i < 5; i++)
            m_Ints.emplace_back(Input::numberPrompt("Integer #" + std::to_string(i + 1), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false));
    }

    void calculateSumOfVectorElements()
    {
        const int sum = std::accumulate(m_Ints.begin(), m_Ints.end(), 0);
        std::cout << "Sum of vector elements: " << sum << '\n';
    }

    void calculateProductOfAllVectorElements()
    {
        const int product = std::accumulate(m_Ints.begin(), m_Ints.end(), 1, std::multiplies());
        std::cout << "Product of vector elements: " << product << '\n';
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