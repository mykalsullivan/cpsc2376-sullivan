//
// Created by msullivan on 3/18/25.
//

#pragma once
#include "Employee.h"

class SalariedEmployee final : public Employee {
    double m_MonthlySalary {};

public:
    SalariedEmployee(std::string name, const int id, const double salary) : Employee(std::move(name), id), m_MonthlySalary(salary)
    {}
    ~SalariedEmployee() override = default;

    [[nodiscard]] double calculateSalary() const override { return m_MonthlySalary; }

    void displayInfo() const override;
};