//
// Created by msullivan on 3/18/25.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>

#include "SalariedEmployee.h"
#include "HourlyEmployee.h"
#include "CommissionEmployee.h"

class Application {
    std::vector<Employee *> m_Employees;

public:
    Application() = default;
    ~Application()
    {
        for (const auto employee : m_Employees)
            delete employee;
    }

    int exec()
    {
        // Open 'employees.txt' with RAII
        std::ifstream file("employees.txt");
        if (!file)
        {
            std::cerr << "Error: Could not open 'employees.txt'\n";
            return 1;
        }

        m_Employees.clear(); // Ensure vector is empty before adding new employees

        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> tokens;
            std::stringstream ss(line);
            std::string token;

            while (ss >> token)
                tokens.emplace_back(token);

            if (tokens.size() < 3) // Type, ID, name
            {
                std::cerr << "Invalid employee format in line: " << line << '\n';
                continue;
            }

            try
            {
                const std::string &type = tokens[0];
                int id = std::stoi(tokens[1]);
                const std::string &name = tokens[2];

                if (Employee *newEmployee = createEmployee(type, id, name, tokens))
                    m_Employees.emplace_back(newEmployee);
                else
                    std::cerr << "Unknown employee type '" << type << "'\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Invalid employee format in line: " << line << " (" << e.what() << ")\n";
            }
        }

        // Display employee list
        for (const auto& employee : m_Employees)
            employee->displayInfo();

        return 0;
    }

private:
    // Helper function to create employees
    static Employee *createEmployee(const std::string& type, const int id, const std::string& name, const std::vector<std::string> &tokens)
    {
        try
        {
            if (type == "Salaried" && tokens.size() >= 4)
                return new SalariedEmployee(name, id, std::stod(tokens[3]));

            if (type == "Hourly" && tokens.size() >= 5)
                return new HourlyEmployee(name, id, std::stod(tokens[3]), std::stoi(tokens[4]));

            if (type == "Commission" && tokens.size() >= 6)
                return new CommissionEmployee(name, id, std::stod(tokens[3]), std::stod(tokens[4]), std::stod(tokens[5]));
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: Failed to create employee (" << e.what() << ")\n";
        }
        return nullptr;
    }
};

int main()
{
    Application app;
    return app.exec();
}