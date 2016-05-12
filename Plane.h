#pragma once

#include "vec3d.h"
#include <vector>

class Plane {
public:
	double a, b, c, d;
	Plane(const vec3d &, const vec3d &, const vec3d &);
	Plane(const std::vector<vec3d> &);
	vec3d getNormal() const;
	bool contains(const vec3d &) const;
};