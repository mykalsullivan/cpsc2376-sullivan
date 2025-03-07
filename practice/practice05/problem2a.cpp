//
// Created by msullivan on 2/26/25.
//

#include "Input.h"
#include <iostream>
#include <limits>

class Application {
	bool m_Running {false};

public:
	Application() = default;
	~Application() = default;

	// Starts the program run loop
	int exec()
	{
		std::cout << "Basic Calculator by M. Sullivan\n";

		m_Running = true;
		while (m_Running)
		{
			const float num1 = Input::numberPrompt("1st number", std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), false);
			const float num2 = Input::numberPrompt("2nd number", std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), false);
			const char operation = Input::textPrompt("Operation [+, -, *, /]", 0, 1, false).at(0);

			calculate(num1, num2, operation);
			if (!Input::boolPrompt("Do it again?")) m_Running = false;
		}
		return 0;
	}

private:
	// Stops the program
	void stop()
	{
		m_Running = false;
	}

	// Read the method name
	template <typename T>
	static void calculate(const T num1, const T num2, const char operation)
	{
		double output {};
		switch (operation)
		{
			case '+':
				output = num1 + num2;
				break;
			case '-':
				output = num1 - num2;
				break;
			case '*':
				output = num1 * num2;
				break;
			case '/':
				output = num1 / num2;
				break;
			default:
				std::cout << "Invalid operation\n"; return;
		}
		std::cout << "Output: " << output << '\n';
	}
};

int main()
{
	Application app;
    return app.exec();
}