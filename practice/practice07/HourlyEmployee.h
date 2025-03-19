//
// Created by msullivan on 3/18/25.
//

#pragma once
#include "Employee.h"

class HourlyEmployee final : public Employee {
    double m_HourlyRate {};
    int m_HoursWorked {};

public:
    HourlyEmployee(std::string name, const int id,
        const double hourlyRate, const int hoursWorked) :
        Employee(std::move(name), id), m_HourlyRate(hourlyRate), m_HoursWorked(hoursWorked)
    {}
    ~HourlyEmployee() override = default;

    [[nodiscard]] double calculateSalary() const override { return m_HourlyRate * m_HoursWorked; }

    void displayInfo() const override;
};