#pragma once
class vec3d {
public:
	double x, y, z;
	vec3d();
	vec3d(double, double, double);
	double getDistance(const vec3d &) const;
	double getSqrDistance(const vec3d &) const;
	vec3d cross(const vec3d &) const;
	double dot(const vec3d &) const;
	vec3d operator+(const vec3d &) const;
	vec3d operator-(const vec3d &) const;
	vec3d operator*(double) const;
	vec3d & operator+=(const vec3d &);
	double length() const;
	vec3d normalized() const;
	double cos(const vec3d &) const;
	double & operator[](size_t);
	double operator[](size_t) const;
	bool equalsByValue(const vec3d &) const;
};