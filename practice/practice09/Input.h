//
// Created by msullivan on 3/2/25.
//

#pragma once
#include <iostream>
#include <limits>

namespace Input
{
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

    inline std::string textPrompt(const std::string &prompt, const int min, const int max, const bool showRange)
    {
        std::string input;
        while (true)
        {
            std::cout << prompt;
            if (showRange) std::cout << " [" << min << '-' << max << "]";
            std::cout << ": ";

            if (!std::getline(std::cin, input))
            {
                std::cerr << "Error reading input\n";
                exit(EXIT_FAILURE);
            }

            if (input.empty())
            {
                std::cout << "Input cannot be empty. Try again.\n";
                continue;
            }

            if (input.size() < static_cast<size_t>(min))
            {
                std::cout << "Input must be at least " << min << " character(s) long\n";
                continue;
            }

            if (input.size() > static_cast<size_t>(max))
            {
                std::cout << "Input must be at most " << max << " character(s) long\n";
                continue;
            }

            return input;
        }
    }

    // Displays a prompt to gather a boolean user value
    inline bool boolPrompt(const std::string &prompt)
    {
        std::cout << prompt << " [y/n]: ";
        char input;
        while (true)
        {
            std::cin >> input;
            std::cin.ignore();
            if (!std::cin.fail())
            {
                switch (input)
                {
                    case 'y': return true;
                    case 'n': return false;
                    default: std::cout << "Invalid input. Try again. [y/n]: ";
                }
            }
            else
            {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "Invalid input. Try again. [y/n]: ";
            }
        }
    }
}