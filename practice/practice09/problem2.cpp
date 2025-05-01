//
// Created by msullivan on 5/1/25.
//

#include <iostream>

struct Point {
    float x;
    float y;
};

// Function to calculate the midpoint between two points (returns a Point object)
Point calcMidpoint(const Point *p1, const Point *p2)
{
    if (p1 && p2) return Point{((p1->x + p2->x) / 2.0f), ((p1->y + p2->y) / 2.0f)};
    return Point{-1.0f, -1.0f};  // Placeholder return value
}

int main()
{
    // Step 1: Create two points with example coordinates
    constexpr Point a{1.0f, 2.0f};
    constexpr Point b{5.0f, 6.0f};

    // Step 2: Call calcMidpoint using pointers to 'a' and 'b'
    const Point mid = calcMidpoint(&a, &b);

    // Step 3: Print the midpoint coordinates
    std::cout << "Midpoint is at (" << mid.x << ", " << mid.y << ")" << std::endl; // Should be (3, 4)

    return 0;
}