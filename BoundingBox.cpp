#include "BoundingBox.h"
#include <algorithm>

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(const Surface &surface) {
	min_corner_ = max_corner_ = surface.vertices[0];
	for (int i = 1; i < surface.vertices.size(); ++i)
		for (int j = 0; j < 3; ++j) {
			min_corner_[j] = std::min(min_corner_[j], surface.vertices[i][j]);
			max_corner_[j] = std::max(max_corner_[j], surface.vertices[i][j]);
		}
}

BoundingBox BoundingBox::operator+(const BoundingBox &other) const {
	BoundingBox result;
	for (int i = 0; i < 3; ++i) {
		result.min_corner_[i] = std::min(min_corner_[i], other.min_corner_[i]);
		result.max_corner_[i] = std::max(max_corner_[i], other.max_corner_[i]);
	}
	return result;
}

BoundingBox & BoundingBox::operator+=(const BoundingBox & other) {
	for (int i = 0; i < 3; ++i) {
		min_corner_[i] = std::min(min_corner_[i], other.min_corner_[i]);
		max_corner_[i] = std::max(max_corner_[i], other.max_corner_[i]);
	}
	return *this;
}

vec3d BoundingBox::getMin() const {
	return min_corner_;
}

vec3d BoundingBox::getMax() const {
	return max_corner_;
}

vec3d BoundingBox::operator[](size_t t) const {
	if (t == 0)
		return min_corner_;
	else
		return max_corner_;
}