#include "IntersectionInfo.h"

IntersectionInfo::IntersectionInfo() : intersects_(false) {}

void IntersectionInfo::setIntersectionSurface(const Surface & new_surface) {
	surface = &new_surface;
}

void IntersectionInfo::setIntersectionPoint(const vec3d & point) {
	intersects_ = true;
	intersection_point_ = point;
}

vec3d IntersectionInfo::getIntersectionPoint() const {
	return intersection_point_;
}

bool IntersectionInfo::intersects() const {
	return intersects_;
}

vec3d IntersectionInfo::getNormal() const {
	vec3d normal;
	if (surface->vertex_normals.size() == 3) {
		vec3d normal;
		double t;
		double area = (surface->vertices[2] - surface->vertices[0]).cross(surface->vertices[1] - surface->vertices[0]).length();
		if (area < 1e-3)
			return normal;
		for (int i = 0; i < 3; ++i) {
			t = (surface->vertices[(i + 2) % 3] - intersection_point_).cross(surface->vertices[(i + 1) % 3] - intersection_point_).length() / area;
			normal += surface->vertex_normals[i] * t;
		}
		return normal;
	}
	if (surface->vertices.size() < 3)
		return normal;
	return (surface->vertices[0] - surface->vertices[1]).cross(surface->vertices[2] - surface->vertices[1]);
}

const Material & IntersectionInfo::getMaterial() const {
	return surface->material;
}

bool IntersectionInfo::betterThan(const IntersectionInfo &other, const vec3d &point) const {
	if (intersects_ != other.intersects_)
		return intersects_;
	if (!intersects_)
		return true;
	return intersection_point_.getSqrDistance(point) < other.intersection_point_.getSqrDistance(point);
}