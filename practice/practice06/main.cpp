//
// Created by msullivan on 3/6/25.
//

#include <iostream>
#include "Fraction.h"
#include "MixedFraction.h"
#include "Input.h"

class Calculator {
    Fraction m_Fraction {0, 1};
    bool m_Running {false};

public:
    int exec()
    {
        m_Running = true;
        while (m_Running)
        {
            const std::string prompt = "Fraction: " + m_Fraction.toString() +
                                        "\nWhat do you want to do with your fraction?"
                                        "\n1. Set value"
                                        "\n2. Add a fraction"
                                        "\n3. Subtract a fraction"
                                        "\n4. Multiply by a fraction"
                                        "\n5. Divide by fraction"
                                        "\n6. Display as mixed fraction"
                                        "\n7. Clear"
                                        "\n8. Throw it in the garbage and exit program"
                                        "\nWell, what is it?";
            const int action = Input::numberPrompt(prompt, 1, 8, true);
            handleAction(action);
        }
        return 0;
    }

private:
    void handleAction(const int action)
    {
        switch (action)
        {
            case 1: set(); break;
            case 2: add(); break;
            case 3: subtract(); break;
            case 4: multiply(); break;
            case 5: divide(); break;
            case 6: displayAsMixedFraction(); break;
            case 7: clear(); break;
            case 8: stop(); break;
            default: break;
        }
    }

    void set()
    {
        m_Fraction = createFraction();
    }

    void add()
    {
        const Fraction newFrac = createFraction();
        m_Fraction = m_Fraction + newFrac;
    }

    void subtract()
    {
        const Fraction newFrac = createFraction();
        m_Fraction = m_Fraction - newFrac;
    }

    void multiply()
    {
        const Fraction newFrac = createFraction();
        m_Fraction = m_Fraction * newFrac;
    }

    void divide()
    {
        const Fraction newFrac = createFraction();
        m_Fraction = m_Fraction / newFrac;
    }

    void displayAsMixedFraction() const
    {

    }

    void clear()
    {
        m_Fraction.setNumerator(0);
        m_Fraction.setDenominator(1);
    }

    void stop()
    {
        m_Running = false;
    }

    // Helper function to create a fraction from numerator and denominator
    Fraction createFraction()
    {
        // Prompt for fraction numerator
        std::string prompt = "Numerator";
        int num = Input::numberPrompt(prompt, INT32_MIN, INT32_MAX, false);

        // Prompt for fraction denominator
        prompt = "Denominator";
        int den = Input::numberPrompt(prompt, INT32_MIN, INT32_MAX, false);

        // Remove negative signs if both the num and den are negative
        if (num < 0 && den < 0)
        {
            num *= -1;
            den *= -1;
        }

        return Fraction(num, den);
    }
};

int main()
{
    Calculator calc;
    return calc.exec();
}