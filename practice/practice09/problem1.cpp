//
// Created by msullivan on 5/1/25.
//

#include <iostream>
#include <iomanip>
#include <limits>
#include "Input.h"

namespace
{
    float redPotion {0.0f};
    float bluePotion {0.0f};
    float *flask {nullptr};
}

void displayPotions()
{
    std::cout << "Red potion: " << std::setprecision(3) << redPotion << "mL\n"
              << "Blue potion: " << std::setprecision(3) << bluePotion << "mL\n";
}

int main()
{
    std::cout << "practice09 : Mykal Sullivan\n";

    std::string input {};
    while (true)
    {
        std::cout << "Options:\n"
                  << "* Red\n"
                  << "* Blue\n"
                  << "* Done\n\n";
        input = Input::textPrompt("Which potion would you like to add liquid to?", 0, std::numeric_limits<int>::max(), false);

        // Process input
        if (input == "done") break;
        else if (input == "red") flask = &redPotion;
        else if (input == "blue") flask = &bluePotion;
        else
        {
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        // Get amount of mL to add
        const float amount = Input::numberPrompt("How many mL of liquid?", 0.0f, std::numeric_limits<float>::max(), false);

        // Add liquid and display potions
        if (flask) *flask += amount;
        displayPotions();
    }

    return 0;
}