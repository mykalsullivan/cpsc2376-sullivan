//
// Created by msullivan on 3/2/25.
//

#pragma once
#include <iostream>

namespace Input
{
    // Displays a prompt to retrieve user input with bounds checking
    template <typename T>
    requires (std::integral<T> || std::floating_point<T>)
    T numberPrompt(const std::string &prompt, const T min, const T max, const bool showRange)
    {
        std::cout << prompt;
        if (showRange) std::cout << " [" << std::to_string(min) << '-' << std::to_string(max) << "]";
        std::cout << ": ";

        float input;
        while (true)
        {
            std::cin >> input;
            if (!std::cin.fail() && input >= min && input <= max) return input;
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input. Try again [" << min << "-" << max << "]: ";
        }
    }

    inline std::string textPrompt(const std::string &prompt, const int min, const int max, const bool showRange)
    {
        std::cout << prompt;
        if (showRange) std::cout << " [" << std::to_string(min) << '-' << std::to_string(max) << "]";
        std::cout << ": ";

        std::string input;
        while (true)
        {
            std::getline(std::cin, input);
            if (input.size() > max)
                std::cout << "Input must be less than " << std::to_string(max + 1) << " character(s) long\n";
            else if (input.size() < min)
                std::cout << "Input must be more than " << std::to_string(min) << " character(s) long\n";
            else
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