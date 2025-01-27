#pragma once
#include <vector>

class Application {
        std::vector<int> m_Vec;
        bool m_Running;

public:
        Application();
        ~Application() = default;
	
	/* Starts program loop */
	int exec();

private:
	/* Prompts user for a number to append to array */
	void addItem();

	/* Prints vector elements to terminal */
	void printVector();

	/* Doubles vector elements */
	void doubleVector();

	/* Calculates and prints sum of vector elements to terminal */
	void findSum();

	/* Prints the multiples of a user-defined value to terminal */
	void printMultiples();

	/* Clears all elements from the internal vector */
	void clearVector();

	/* Stops main program loop and terminates the program */
	void exit();
};

