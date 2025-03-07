//
// Created by msullivan on 2/26/25.
//

#include "Input.h"
#include <iostream>
#include <vector>

class Application {
    bool m_Running {false};
    std::vector<int> m_Ints {};

public:
    Application() = default;
    ~Application() = default;

    int exec()
    {
        std::cout << "Iterator Loop by M. Sullivan\n";

        gatherIntegers();
        printVecUsingIterators();
        findSumOfEvenNumbersUsingIterators();

        return 0;
    }

private:
    void gatherIntegers()
    {
        for (int i = 0; i < 5; i++)
            m_Ints.emplace_back(Input::numberPrompt("Integer #" + std::to_string(i + 1), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false));
    }

    void printVecUsingIterators()
    {
        int i = 0;
        for (auto it = m_Ints.begin(); it != m_Ints.end(); ++it)
            std::cout << ++i << ": " << *it << '\n';
    }

    void findSumOfEvenNumbersUsingIterators()
    {
        int sum = 0;
        for (auto it = m_Ints.begin(); it != m_Ints.end(); ++it)
            if (*it.base() % 2 == 0)
                sum += *it;

        std::cout << "Sum of even numbers: " << sum << '\n';
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