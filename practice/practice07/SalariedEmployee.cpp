//
// Created by msullivan on 3/18/25.
//

#include "SalariedEmployee.h"
#include "FormatCurrency.h"
#include <iostream>

void SalariedEmployee::displayInfo() const
{
    std::cout << "ID: " << m_ID << ", "
                 "Name: " << m_Name << ", "
                 "Type: Salary, "
                 "Monthly Salary: " << Format::currency(calculateSalary()) << '\n';
}