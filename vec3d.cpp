#include "vec3d.h"
#include <cmath>

vec3d::vec3d() : x(0), y(0), z(0) {}
vec3d::vec3d(double x, double y, double z) : x(x), y(y), z(z) {}

double & vec3d::operator[](size_t t) {
	if (t == 0)
		return x;
	if (t == 1)
		return y;
	return z;
}

double vec3d::operator[](size_t t) const {
	if (t == 0)
		return x;
	if (t == 1)
		return y;
	return z;
}

double vec3d::getSqrDistance(const vec3d &other) const {
	return pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2);
}

double vec3d::getDistance(const vec3d &other) const {
	return sqrt(getSqrDistance(other));
}

vec3d vec3d::cross(const vec3d &other) const {
	return vec3d(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

double vec3d::dot(const vec3d &other) const {
	return x * other.x + 
		   y * other.y + 
		   z * other.z;
}

vec3d vec3d::operator+(const vec3d &other) const {
	return vec3d(
		x + other.x,
		y + other.y,
		z + other.z
	);
}

vec3d & vec3d::operator+=(const vec3d &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vec3d vec3d::operator-(const vec3d &other) const {
	return vec3d(
		x - other.x,
		y - other.y,
		z - other.z
	);
}

vec3d vec3d::operator*(double t) const {
	return vec3d(
		x * t,
		y * t,
		z * t
	);
}

double vec3d::length() const {
	return sqrt(x * x + y * y + z * z);
}

vec3d vec3d::normalized() const {
	return (*this) * (1 / length());
}

double vec3d::cos(const vec3d &other) const {
	if (getDistance(other) < 1e-3)
		return 0;
	return dot(other) / length() / other.length();
}

bool vec3d::equalsByValue(const vec3d &other) const {
	return abs(x - other.x) < 1e-3 && abs(y - other.y) < 1e-3 && abs(z - other.z) < 1e-3;
}
