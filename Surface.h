#pragma once

#include "vec3d.h"
#include "Material.h"
#include <vector>

class Surface {
public:
	Material material;
	std::vector<vec3d> vertices;
	std::vector<vec3d> texture_vertices;
	std::vector<vec3d> vertex_normals;
	bool containsPoint(const vec3d &) const;
};