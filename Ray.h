#pragma once

#include "vec3d.h"
#include "Surface.h"
#include "IntersectionInfo.h"
#include "Plane.h"
#include "BoundingBox.h"

class Ray {
public:
	Ray();
	Ray(const vec3d &, const vec3d &);
	vec3d position, direction;
	IntersectionInfo intersect(const Surface &) const;
	bool hasIntersection(const Plane &) const;
	bool hasIntersection(const BoundingBox &) const;
	vec3d intersect(const Plane &) const;
};