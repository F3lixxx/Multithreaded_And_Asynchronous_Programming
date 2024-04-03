#pragma once 
#define _USE_MATH_DEFINES
#include <cmath>

enum class figures
{
	line, sqr, cube, circle, cylinder
};

class Shape1
{
public:
	Shape1() = default;
	int getType() { return type; }

	virtual void shift(int m, int n, int k) = 0;
	virtual void scaleX(int _a) = 0;
	virtual void scaleY(int d) = 0;
	virtual void scaleZ(int e) = 0;
	virtual void scale(int s) = 0;

protected:
	int type;
	int a = 0, b = 0, c = 0;
	double volume = 0;
	double square = 0;
	int x1 = 0, y1 = 0, z1 = 0,
		x2 = 0, y2 = 0, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0,
		x5 = 0, y5 = 0, z5 = 0,
		x6 = 0, y6 = 0, z6 = 0,
		x7 = 0, y7 = 0, z7 = 0,
		x8 = 0, y8 = 0, z8 = 0;
		
     	virtual void calculatorSquare(const int& a, const int& b, const int& c) = 0;
		virtual void calculatorVolume(const int& a, const int& b, const int& c) = 0;
};

class Shape2
{
	Shape2() = default;
	int getType() {return type};

protected:
	int type;
	double volume;
	double square;
	double height;
	double radius;
	int x1 = 0, y1 = 0; 
	
	virtual void calculatorSquare(const double& R, const double& H) = 0;
	virtual void calculatorVolume(const double& R, const double& H) = 0;
};


