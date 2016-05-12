#include "Surface.h"

bool Surface::containsPoint(const vec3d &point) const {
	double area = 0;
	vec3d area_vector;
	for (int i = 2; i < vertices.size(); ++i)
		area_vector += (vertices[i - 1] - vertices[0]).cross(vertices[i] - vertices[0]);
	area = area_vector.length();
	double calculated = 0;
	for (int i = 0; i < vertices.size(); ++i)
		calculated += (vertices[i] - point).cross(vertices[(i + 1) % 3] - point).length();
	return calculated < area + 1e-3;
}