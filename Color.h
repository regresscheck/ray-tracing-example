#pragma once
#using <system.drawing.dll>

using namespace System;

class Color {
public:
	double r, g, b;
	Color();
	Color(double, double, double);
	operator Drawing::Color();
	Color operator*(double x) const;
	Color & operator+=(const Color &);
};