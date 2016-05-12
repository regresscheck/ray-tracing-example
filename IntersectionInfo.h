#pragma once

#include "vec3d.h"
#include "Surface.h"

class IntersectionInfo {
private:
	bool intersects_;
	vec3d intersection_point_;
	const Surface * surface;
public:
	IntersectionInfo();
	void setIntersectionSurface(const Surface &);
	void setIntersectionPoint(const vec3d &);
	vec3d getIntersectionPoint() const;
	bool intersects() const;
	vec3d getNormal() const;
	const Material & getMaterial() const;
	bool betterThan(const IntersectionInfo &other, const vec3d &) const;
};