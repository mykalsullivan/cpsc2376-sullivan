//
// Created by msullivan on 4/30/25.
//

#pragma once

class Shape {

public:
    Shape() = default;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
};
