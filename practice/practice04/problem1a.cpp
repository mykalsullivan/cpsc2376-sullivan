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
		std::cout << "Temperature Converter by M. Sullivan\n";

		m_Running = true;
		while (m_Running)
		{
			std::string prompt {"Menu:\n1. Convert Fahrenheit to Celsius\n2. Convert Celsius to Fahrenheit\n3. Exit\nWhat do you want to do?"};
			handleAction(static_cast<int>(getNumericInput(prompt, 1, 3, false)));
		}
		return 0;
	}

	// Stops the program
	void stop()
	{
		m_Running = false;
	}

private:
	// Read the method name
	static void convertTemperature(const char scale = 'C')
	{
		// Select temperature scale
		std::string prompt;
		float minTemp {};
		char newScale;
		switch (scale)
		{
			case 'f':
			case 'F':
				prompt = "Temperature [> -273.15 *C]";
				minTemp = -273.15f;
				newScale = 'F';
				break;
			case 'c':
			case 'C':
				prompt = "Temperature [> -459.67 *F]";
				minTemp = -459.67f;
				newScale = 'C';
				break;
			default:
				std::cout << "Invalid scale.\n"; return;
		}
		float temp = getNumericInput(prompt, minTemp, static_cast<float>(std::numeric_limits<double>::max()), false);

		// Convert temperature
		if (scale == 'c' || scale == 'C')
		{
			temp = ((temp - 32.0f) * (5.0f / 9.0f));
		}
		else if (scale == 'f' || scale == 'F')
		{
			temp = ((temp * (5.0f / 9.0f))) + 32.0f;
		}

		// Print converted temperature
		std::cout << std::to_string(temp) << " *" << newScale << '\n';
	}

	// Helper function to perform an action based on input
	void handleAction(const int action)
	{
		switch (action)
		{
			case 1: convertTemperature('c'); break;
			case 2: convertTemperature('f'); break;
			case 3: stop(); break;
			default: break;
		}
	}

	// Displays a prompt to retrieve user input with bounds checking
	static float getNumericInput(const std::string &prompt, const float min, const float max, bool showRange)
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