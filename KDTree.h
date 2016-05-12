#pragma once

#include "Surface.h"
#include "BoundingBox.h"
#include <vector>
#include "IntersectionInfo.h"
#include "Ray.h"

class KDTree {
private:
	struct Node {
		BoundingBox box;
		Node *left, *right;
		Surface surface;
		Node();
		Node(const Surface &);
		~Node();
		void updateBox();
	};
	
	Node * buildTree(std::vector<Surface>::iterator, std::vector<Surface>::iterator, int);
	Node * root;
	IntersectionInfo intersect(const Node *, const Ray &) const;
public:
	KDTree();
	KDTree(std::vector<Surface>);
	~KDTree();
	IntersectionInfo intersect(const Ray &) const;
};