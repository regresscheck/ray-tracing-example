#include "Color.h"

Color::Color() : r(0), g(0), b(0) {}
Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}
Color::operator Drawing::Color() {
	return Drawing::Color::FromArgb(255 * r, 255 * g, 255 * b);
}

Color Color::operator*(double x) const {
	return Color(r * x, g * x, b * x);
}

Color & Color::operator+=(const Color & other) {
	r += other.r;
	g += other.g;
	b += other.b;
	return *this;
}