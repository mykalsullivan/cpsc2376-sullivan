//
// Created by msullivan on 3/10/25.
//

#include <iostream>
#include <random>
#include <vector>
#include <limits>

namespace Input {
    // Displays a prompt to retrieve user input with bounds checking
    template <typename T>
    T numberPrompt(const std::string &prompt, const T min, const T max, const bool showRange)
    {
        T input;
        while (true)
        {
            std::cout << prompt;
            if (showRange) std::cout << " [" << min << '-' << max << "]";
            std::cout << ": ";

            std::cin >> input;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!std::cin.fail() && input >= min && input <= max) return input;

            std::cout << "Invalid input. Try again.\n";
        }
    }
}

// Forward declaration(s)
void calculateSumOfAllNumbers(std::vector<int> vec);
void findMinAndMax(std::vector<int> &vec);
void findAverage(const std::vector<int> &vec);

int main()
{
    std::vector<int> randomInts {};

    // 1. Ask how many random numbers to generate
    const std::string prompt = "How many random numbers?";
    int randomIntCount = Input::numberPrompt(prompt, 1, 100, true);
    randomInts.resize(randomIntCount);

    // 2. Generate that many random integers between 1 and 100 and store them
    //    in a std::vector<int>

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution dist(1, 100);
    for (size_t i = 0; i < randomIntCount; ++i)
        randomInts.at(i) = dist(mt);

    // 3. Implement functions using pass-by-value, pass-by-reference, and pass-by-const-reference
    //    as apppropriate:
    //      - A function that calculates the sum of all numbers.
    //      - A function that finds and returns both the minimum and maximum numbers
    //      - A function that calculates and returns the average

    calculateSumOfAllNumbers(randomInts);
    findMinAndMax(randomInts);
    findAverage(randomInts);

    return 0;
}

void calculateSumOfAllNumbers(std::vector<int> vec)
{
    int sum {0};
    for (const auto i : vec)
        sum += i;

    std::cout << "Sum: " << std::to_string(sum) << '\n';
}

void findMinAndMax(std::vector<int> &vec)
{

    int min = vec.at(0), max = vec.at(0);

    for (int i = 1; i < vec.size(); ++i)
    {
        if (vec.at(i) < min) min = vec.at(i);
        if (vec.at(i) > max) max = vec.at(i);
    }
    std::cout << "Min: " << min << ", Max: " << max << std::endl;
}

void findAverage(const std::vector<int> &vec)
{
    int sum {0};
    for (int i = 0; i < vec.size(); ++i)
        sum += vec.at(i);

    const double average = static_cast<double>(sum) / static_cast<double>(vec.size());

    std::cout << "Average: " << average << std::endl;
}
