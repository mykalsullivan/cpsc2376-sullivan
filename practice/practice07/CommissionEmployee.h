//
// Created by msullivan on 3/18/25.
//

#pragma once
#include "Employee.h"

class CommissionEmployee final : public Employee {
    double m_BaseSalary {};
    double m_SalesAmount {};
    double m_CommissionRate {};

public:
    CommissionEmployee(std::string name, const int id,
        const double baseSalary, const double salesAmount, const double commissionRate) :
    Employee(std::move(name), id), m_BaseSalary(baseSalary), m_SalesAmount(salesAmount), m_CommissionRate(commissionRate)
    {}
    ~CommissionEmployee() override = default;

    [[nodiscard]] double calculateSalary() const override { return m_BaseSalary + (m_SalesAmount * m_CommissionRate); }

    void displayInfo() const override;

private:
};