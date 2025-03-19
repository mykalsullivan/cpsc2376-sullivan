//
// Created by msullivan on 3/19/25.
//

#pragma once
#include <sstream>
#include <iomanip>

namespace Format
{
    inline std::string currency(const double amount)
    {
        std::stringstream ss;
        ss << '$' << std::fixed << std::setprecision(2) << amount;
        return ss.str();
    }

    inline std::string percentage(double percent)
    {
        percent *= 100;
        std::stringstream ss;
        ss << std::setprecision(0) << percent << '%';
        return ss.str();
    }
}