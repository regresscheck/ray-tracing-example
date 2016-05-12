#pragma once
#include <vector>
#include "vec3d.h"
#include "ObjReader.h"
#include "Surface.h"
#include "IntersectionInfo.h"
#include "Ray.h"
#include "KDTree.h"

class Model {
	friend class ObjReader;
private:
	KDTree * tree;
public:
	Model(const Model&) = delete;
	Model operator=(const Model &) = delete;
	Model();
	Model(const std::vector<Surface> &);
	Model(Model &&);
	~Model();
	Model & operator=(Model &&);
	static Model readFromObj(const char *);
	bool initialized() const;
	IntersectionInfo intersect(const Ray &) const;
};