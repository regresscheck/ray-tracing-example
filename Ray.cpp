#include "Ray.h"
#include "Plane.h"
#include <cmath>
#include <iostream>

Ray::Ray() {};

Ray::Ray(const vec3d &position, const vec3d &direction) : position(position), direction(direction) {}

IntersectionInfo Ray::intersect(const Surface &surface) const {
	Plane plane(surface.vertices);
	if (!hasIntersection(plane))
		return IntersectionInfo();
	IntersectionInfo result;
	vec3d intersection = intersect(plane);
	if (surface.containsPoint(intersection) && direction.dot(intersection - position) > 0) {
		result.setIntersectionPoint(intersection);
		result.setIntersectionSurface(surface);
	}
	return result;
}

vec3d Ray::intersect(const Plane &plane) const {
	vec3d normal = plane.getNormal();
	double t = (position.dot(normal) + plane.d) / (direction.dot(normal));
	return position + (direction * -t);
}

bool Ray::hasIntersection(const Plane &plane) const {
	vec3d normal = plane.getNormal();
	return abs(direction.dot(normal)) > 1e-3; // TODO: move constant
}

bool Ray::hasIntersection(const BoundingBox &box) const {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 2; ++j) {
			double t;
			if (abs(direction[i]) < 1e-3) {
				if (abs(position[i] - box[j][i]) < 1e-3)
					t = 0;
				else
					continue;
			}
			else {
				t = (box[j][i] - position[i]) / direction[i];
			}
			if (t < -1e-3)
				continue;
			vec3d intersection = position + direction * t;
			bool intersected = true;
			for (int k = 0; k < 3; ++k) {
				if (k != i && (box[0][k] > intersection[k] + 1e-3 || (intersection[k] > box[1][k] + 1e-3)))
					intersected = false;
			}
			if (intersected)
				return true;
		}
	}
	return false;
}