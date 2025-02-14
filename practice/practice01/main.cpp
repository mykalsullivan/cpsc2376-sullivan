#include <iostream>
#include <vector>

class Application {
	std::vector<int> m_Vec;
	bool m_Running;

public:
	Application() : m_Running(true)
	{
		/* Using .reserve() is redundant considering the vector will never become this large, but it wouldn't hurt to remind myself of the method's existence. */
		m_Vec.reserve(1024);
    }

	~Application() = default;

	/* Starts program loop */
	int exec()
    {
		std::cout << "** Text-Based Vector Operations,  by M. Sullivan **\n";

		while (m_Running)
		{
			// 1. Print menu options
			std::cout << "1. Add item\n"
					"2. Print vector\n"
						   "3. Double vector\n"
					"4. Find sum\n"
					"5. Print multiples\n"
					"6. Clear vector\n"
					"0. Exit\n\n";

			// 2. Prompt user input
			int input {};
			bool flag {true}; // Loop continues until user enters valid selection
			while (flag)
			{
				flag = false;

				std::cout << "-> ";
				std::cin >> input;
				if (std::cin.fail())
				{
					flag = true;
					std::cin.clear();
					std::cin.ignore();
					std::cout << "Please enter a numeric value\n";
					continue;
				}

				if (input > 6 || input < 0)
				{
					flag = true;
					std::cout << "Invalid option.\n";
				}
			}

			// 3. Process user input
			switch (input)
			{
				case 0: exit(); break;
				case 1: addItem(); break;
				case 2: printVector(); break;
				case 3: doubleVector(); break;
				case 4: findSum(); break;
				case 5: printMultiples(); break;
				case 6: clearVector(); break;
				default: break;
			}
		}
		return 0;
    }

private:
	/* Prompts user for a number to append to array */
	void addItem()
    {
		std::cout << "--- Add Item ---\n";

		// 1. Prompt for int value
		int input {};
		bool flag {true};

		while (flag)
		{
			flag = false;

			std::cout << "int value: ";
			try
			{
				std::cin >> input;
				std::cin.get();
			}
			catch (const std::exception &e)
			{
				flag = true;
				continue;
			}
		}

		// 2. Place input into vector
		m_Vec.emplace_back(input);
		std::cout << "Appended value '" << std::to_string(input) << "' to vector.\n"
				"Vector now contains " << m_Vec.size() << " item(s).\n\n";
    }

	/* Prints vector elements to terminal */
	void printVector()
    {
		std::cout << "--- Vector Items ---\n";

		// 0. Check if vector is empty
		if (m_Vec.empty())
		{
			std::cout << "(empty)\n\n";
			return;
		}

		// 1. Print vector items
		for (int i {0}; i < m_Vec.size(); ++i)
			std::cout << std::to_string((1 + i)) << ": " << m_Vec.at(i) << '\n';

		std::cout << std::endl;
    }

	/* Doubles vector elements */
	void doubleVector()
    {
		std::cout << "--- Double Vector Items ---\n";

		// 0. Check if vector is empty
		if (m_Vec.empty())
		{
			std::cout << "Cannot double items in an empty vector. Add some, then try again.\n\n";
			return;
		}

		for (auto &i : m_Vec) i *= 2;
		std::cout << "Doubled vector items.\n\n";
    }

	/* Calculates and prints sum of vector elements to terminal */
	void findSum()
    {
		std::cout << "--- Find Sum ---\n";

		int sum {0};
		for (const auto &i : m_Vec) sum += i;

		std::cout << "Sum: " << std::to_string(sum);
		if (m_Vec.empty()) std::cout << " (vector empty)";
		std::cout << "\n\n";
    }

	/* Prints the multiples of a user-defined value to terminal */
	void printMultiples()
    {
		std::cout << "--- Find Vector Multiples ---\n";

		// 0. Check for empty vector
		if (m_Vec.empty())
		{
			std::cout << "Vector empty; add items, then try again.\n\n";
			return;
		}

		// 1. Prompt for multiplier
		int multiplier {};
		std::cout << "Multiplier: ";
		try
		{
			std::cin >> multiplier;
			std::cin.get();
		}
		catch (const std::exception &e)
		{
			std::cout << "You cannot multiply numbers by characters using basic arithmetic. That doesn't make any sense. What's wrong with you?\n";
			return;
		}

		// 2. Find vector multiples and print each set to terminal
		for (int i {0}; i < m_Vec.size(); ++i)
			std::cout <<  std::to_string(1 + i) <<
				": " << std::to_string(m_Vec[i]) <<
				" * " << std::to_string(multiplier) <<
				" = " << std::to_string(m_Vec[i] * multiplier) << '\n';
		std::cout << std::endl;
    }

	/* Clears all elements from the internal vector */
	void clearVector()
    {
		std::cout << "--- Clear Vector ---\n";

		// 0. Check if vector is empty
		if (m_Vec.empty())
		{
			std::cout << "Redundant clear; vector already empty.\n\n";
			return;
		}

		// 1. Confirm whether user wants to clear vector
		bool flag {true};
		while (flag)
		{
			flag = false;
			std::cout << "Are you sure? [y/n]: ";

			char input {};
			std::cin >> input;
			std::cin.get();

			switch (input)
			{
				case 'y':
				case 'Y':
					m_Vec.clear();
				std::cout << "Vector cleared.\n\n";
				break;
				case 'n':
				case 'N':
					std::cout << "Aborted.\n\n";
				break;
				default:
					flag = true;
			}
		}
    }

	/* Stops main program loop and terminates the program */
	void exit()
    {
    	m_Running = false;
    }
};

int main()
{
	Application app;
	return app.exec();
}
