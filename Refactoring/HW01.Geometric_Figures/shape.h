#pragma once

#include <string>

struct Point {
    int x, y, z;
};

class Shape {
public:
    static const int LINE = 0;
    static const int SQUARE = 1;
    static const int CUBE = 2;
    static const int CIRCLE = 3;
    static const int CYLINDER = 4;

    Shape() = default;
    Shape(int type, const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5, const Point& p6, const Point& p7, const Point& p8);
    Shape(int type, const Point& p1, const Point& p2, double R, double H);

    int getType() const { return type; }

    int type = 0;
    Point points[8];
    double volume = 0.0;
    double square = 0.0;
    double height = 0.0;
    double radius = 0.0;
};
