//
// Created by msullivan on 2/20/25.
//

#include <iostream>
#include <limits>
#include "Input.h"

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
			handleAction(static_cast<int>(Input::numberPrompt(prompt, 1, 3, false)));
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
		float temp = Input::numberPrompt(prompt, minTemp, static_cast<float>(std::numeric_limits<double>::max()), false);

		// Convert temperature
		if (scale == 'c' || scale == 'C') // Fahrenheit to celsius
		{
			temp = ((temp - 32.0f) * (5.0f / 9.0f));
		}
		else if (scale == 'f' || scale == 'F') // Celsius to fahrenheit
		{
			temp = ((temp * (9.0f / 5.0f))) + 32.0f;
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
};

int main()
{
	Application app;
	return app.exec();
}