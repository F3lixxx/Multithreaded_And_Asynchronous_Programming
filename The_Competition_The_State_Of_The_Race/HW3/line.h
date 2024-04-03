#pragma once
#include "shape.h"

class Line : public Shape1
{
public:
	Line(const int& _x1, const int& _y1, const int& _x2, const int& _y2);
	void shift(int m, int n, int k);
	void scaleX(int _a) override;
	void scaleY(int d) override;
	void scaleZ(int e) override;
	void scale(int s) override;

protected:
	void calculatorSquare(const int& a, const int& b, const int& c) override;
	void calculatorVolume(const int& a, const int& b, const int& c)override;
};