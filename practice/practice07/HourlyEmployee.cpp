//
// Created by msullivan on 3/18/25.
//

#include "HourlyEmployee.h"
#include "FormatCurrency.h"
#include <iostream>

void HourlyEmployee::displayInfo() const
{
    std::cout << "ID: " << m_ID << ", "
                 "Name: " << m_Name << ", "
                 "Type: Hourly, "
                 "Hours Worked: " << m_HoursWorked << ", "
                 "Hourly Rate: " << Format::currency(m_HourlyRate) << ", "
                 "Salary: " << Format::currency(calculateSalary()) << '\n';
}