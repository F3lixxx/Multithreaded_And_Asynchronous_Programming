#define _USE_MATH_DEFINES
#include "shape.h"
#include <cmath>

Line::Line(const Point& _p1, const Point& _p2) : p1(_p1), p2(_p2) {
    type = Shape::LINE;
}

Square::Square(const std::vector<Point>& _vertices) : vertices(_vertices) {
    type = Shape::SQUARE;
}

Cube::Cube(const std::vector<Point>& _vertices) : vertices(_vertices) {
    type = Shape::CUBE;
}

Circle::Circle(const Point& _center, double _radius) : center(_center), radius(_radius) {
    type = Shape::CIRCLE;
}

Cylinder::Cylinder(const Point& _center, double _radius, double _height) : center(_center), radius(_radius), height(_height) {
    type = Shape::CYLINDER;
}

double Line::calculateSquare() const {
    return 0.0;
}

double Line::calculateVolume() const {
    return 0.0;
}

double Square::calculateSquare() const {
    if (vertices.size() != 4)
        return 0.0;
    // Расчет площади квадрата
    // Мы можем предположить, что первые четыре точки образуют квадрат
    double sideLength = std::sqrt((vertices[1].x - vertices[0].x) * (vertices[1].x - vertices[0].x) +
                                  (vertices[1].y - vertices[0].y) * (vertices[1].y - vertices[0].y));
    return sideLength * sideLength;
}

double Square::calculateVolume() const {
    return 0.0;
}

double Cube::calculateSquare() const {
    return 0.0; // Предположим, что метод реализован для расчета площади куба.
}

double Cube::calculateVolume() const {
    return 0.0; // Предположим, что метод реализован для расчета объема куба.
}

double Circle::calculateSquare() const {
    return M_PI * radius * radius;
}

double Circle::calculateVolume() const {
    return 0.0;
}

double Cylinder::calculateSquare() const {
    return M_PI * radius * radius + 2 * M_PI * radius * height;
}

double Cylinder::calculateVolume() const {
    return M_PI * radius * radius * height;
}
