#include "Plane.h"
#include <cmath>

Plane::Plane(const vec3d &first, const vec3d &second, const vec3d &third) {
	vec3d normal = (first - second).cross(third - second);
	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = -1 * (first.x * a + first.y * b + first.z * c);
}

Plane::Plane(const std::vector<vec3d> & vertices) : Plane(vertices[0], vertices[1], vertices[2]) {}

vec3d Plane::getNormal() const {
	return vec3d(a, b, c);
}

bool Plane::contains(const vec3d &point) const {
	return std::abs(a * point.x + b * point.y + c * point.z + d) < 1e-3;
}