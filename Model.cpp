#include "Model.h"

Model::Model() : tree(nullptr) {}

Model::~Model() {
	if (tree)
		delete tree;
}

Model::Model(Model && model) {
	tree = model.tree;
	model.tree = nullptr;
}

Model::Model(const std::vector<Surface> & surfaces) {
	tree = new KDTree(surfaces);
}

Model & Model::operator=(Model && model) {
	tree = model.tree;
	model.tree = nullptr;
	return *this;
}

Model Model::readFromObj(const char * filename) {
	return ObjReader::readFromFile(filename);
}
bool Model::initialized() const {
	return bool(tree);
}

IntersectionInfo Model::intersect(const Ray &ray) const {
	IntersectionInfo result;/*
	for (const Surface & surface : surfaces) {
		IntersectionInfo current = ray.intersect(surface);
		if (current.intersects() && (!result.intersects() ||
			ray.position.getDistance(result.getIntersectionPoint()) > ray.position.getDistance(current.getIntersectionPoint()))) {
			result = current;
		}
	}*/
	result = tree->intersect(ray);
	return result;
}