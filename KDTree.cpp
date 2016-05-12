#include "KDTree.h"
#include "Plane.h"
#include <algorithm>

KDTree::Node::Node(): left(nullptr), right(nullptr) {}

KDTree::Node::Node(const Surface &new_surface) : left(nullptr), right(nullptr) {
	surface = new_surface;
	box = BoundingBox(new_surface);
}

KDTree::Node::~Node() {
	if (left)
		delete left;
	if (right)
		delete right;
}

void KDTree::Node::updateBox() {
	if (left)
		box += left->box;
	if (right)
		box += right->box;
}

KDTree::KDTree() {
	root = new Node();
}

KDTree::~KDTree() {
	if (root)
		delete root;
}

KDTree::Node * KDTree::buildTree(std::vector<Surface>::iterator first, std::vector<Surface>::iterator last, int dimension) {
	if (first == last)
		return nullptr;
	int middle = (last - first) / 2;
	std::nth_element(first, first + middle, last, 
		[dimension](const Surface &left, const Surface &right) {
			return BoundingBox(left)[0][dimension] < BoundingBox(right)[0][dimension];
		});
	Node * result = new Node(*(first + middle));
	result->left = buildTree(first, first + middle, (dimension + 1) % 3);
	result->right = buildTree(first + middle + 1, last, (dimension + 1) % 3);
	result->updateBox();
	return result;
}

KDTree::KDTree(std::vector<Surface> surfaces) {
	if (surfaces.size() == 0)
		root = new Node();
	else
		root = buildTree(surfaces.begin(), surfaces.end(), 0);
}

IntersectionInfo KDTree::intersect(const Ray &ray) const {
	return intersect(root, ray);
}

IntersectionInfo KDTree::intersect(const Node *root, const Ray &ray) const {
	if (!ray.hasIntersection(root->box))
		return IntersectionInfo();
	IntersectionInfo result;
	if (!Plane(root->surface.vertices).contains(ray.position)) {
		result = ray.intersect(root->surface);
	}
	if (root->left) {
		IntersectionInfo current = intersect(root->left, ray);
		if (current.betterThan(result, ray.position))
			result = current;
	}
	if (root->right) {
		IntersectionInfo current = intersect(root->right, ray);
		if (current.betterThan(result, ray.position))
			result = current;
	}
	return result;
}

