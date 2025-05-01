//
// Created by msullivan on 4/30/25.
//

#pragma once
#include "Shape.h"

#include <cmath>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

class Circle : public Shape {
    double m_Radius {};
public:
    Circle(double radius = 0.0f) : m_Radius(radius) {}
    ~Circle() override = default;
    double getArea() const override { return m_Radius * M_PI; }
};