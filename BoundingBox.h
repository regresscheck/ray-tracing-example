#pragma once
#include "vec3d.h"
#include "Surface.h"
#include "BoundingBox.h"

class BoundingBox {
private:
	vec3d min_corner_, max_corner_;
public:
	BoundingBox();
	BoundingBox(const Surface &);
	BoundingBox operator+(const BoundingBox &) const;
	BoundingBox & operator+=(const BoundingBox &);
	vec3d getMin() const;
	vec3d getMax() const;
	vec3d operator[](size_t) const;
};