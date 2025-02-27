//
// Created by msullivan on 2/20/25.
//

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
		while (m_Running)
		{

		}
	}

	// Stops the program
	void stop()
	{
		m_Running = false;
	}

	// Read the method name
	void convertCelsiusToFarenheit()
	{
		getNumericInput("Temperature [> -273.15 *C]", -273.15, std::numeric_limits<double>::max());
	}

	// Read the method name
	void convertFarenheitToCelsius()
	{

	}

	// Helper function to perform an action based on input
	void handleAction(const int action)
	{
		switch (action)
		{
			case 1: convertCelsiusToFarenheit(); break;
			case 2: convertFarenheitToCelsius(); break;
			case 3: stop(); break;
			default: break;
		}
	}

	// Displays a prompt to retrieve user input with bounds checking
	static double getNumericInput(const std::string &prompt, const double min, const double max)
	{
		std::cout << prompt << " [" << std::to_string(min) << '-' << std::to_string(max) << "]: ";
		double input;
		while (true)
		{
			std::cin >> input;
			if (!std::cin.fail() && input >= min && input <= max) return input;
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input. Try again [" << min << "-" << max << "]: ";
		}
	}

	// Displays a prompt to gather a boolean user value
	static bool getBoolInput(const std::string &prompt)
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
};

int main()
{
	Application app;
	return app.exec();
}