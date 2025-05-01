//
// Created by msullivan on 4/30/25.
//

#pragma once
#include "Shape.h"

class Rectangle : public Shape {
    double m_Length {}, m_Width {};
public:
    Rectangle(double length = 0.0f, double width = 0.0f) : m_Length(length), m_Width(width) {}
    ~Rectangle() override = default;
    double getArea() const override { return m_Length * m_Width; }
};