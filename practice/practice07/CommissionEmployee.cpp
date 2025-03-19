//
// Created by msullivan on 3/18/25.
//

#include "CommissionEmployee.h"
#include "FormatCurrency.h"
#include <iostream>

void CommissionEmployee::displayInfo() const
{
    std::cout << "ID: " << m_ID << ", "
                 "Name: " << m_Name << ", "
                 "Type: Commission, "
                 "Base Salary: " << Format::currency(m_BaseSalary) << ", "
                 "Sales: " << Format::currency(m_SalesAmount) << ", "
                 "Commission Rate: " << Format::percentage(m_CommissionRate) << ", "
                 "Salary: " << Format::currency(calculateSalary()) << '\n';
}