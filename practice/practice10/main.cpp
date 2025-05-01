#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

bool readShapesFile(std::vector<std::unique_ptr<Shape>> &shapes)
{
    std::ifstream file("shapes.txt");

    if (!file)
    {
        std::cout << "Error: Could not open 'shapes.txt'\n";
        return false;
    }

    std::string line;
    int lineNumber {0};
    while (std::getline(file, line))
    {
        ++lineNumber;

        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;

        while (ss >> token)
            tokens.emplace_back(token);

        if (tokens.empty())
        {
            std::cout << "Invalid shape format at line: " << lineNumber << '\n';
            continue;
        }

        const std::string& type = tokens[0];
        try {
            if (type == "Circle")
            {
                if (tokens.size() < 2)
                {
                    std::cout << "Invalid Circle format at line: " << lineNumber << '\n';
                    continue;
                }
                const double radius = std::stod(tokens[1]);
                shapes.emplace_back(std::make_unique<Circle>(radius));
            }
            else if (type == "Rectangle")
            {
                if (tokens.size() < 3)
                {
                    std::cout << "Invalid Rectangle format at line: " << lineNumber << '\n';
                    continue;
                }
                const double length = std::stod(tokens[1]);
                const double width = std::stod(tokens[2]);
                shapes.emplace_back(std::make_unique<Rectangle>(length, width));
            }
            else
            {
                std::cout << "Unknown shape type: " << type << " at line " << lineNumber << '\n';
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "Error parsing line: " << lineNumber << " (" << e.what() << ")\n";
        }
    }
    return true;
}

void printAllAreas(const std::vector<std::unique_ptr<Shape>> &shapes)
{
    for (const auto &shape : shapes)
        std::cout << "Area: " << std::setprecision(4) << shape->getArea() << '\n';
}

int main()
{
    std::cout << "practice10 : Mykal Sullivan\n\n";

    std::vector<std::unique_ptr<Shape>> shapes;
    readShapesFile(shapes);
    printAllAreas(shapes);

    return 0;
}