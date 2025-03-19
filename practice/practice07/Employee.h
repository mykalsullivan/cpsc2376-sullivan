//
// Created by msullivan on 3/18/25.
//

#pragma once
#include <string>

class Employee {
protected:
    int m_ID;
    std::string m_Name;

public:
    Employee(std::string name, const int id) : m_ID(id), m_Name(std::move(name))
    {}
    virtual ~Employee() = default;

    [[nodiscard]] virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
};