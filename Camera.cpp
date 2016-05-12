#include "Camera.h"

Camera::Camera() {}
Camera::Camera(int width, int height) : width(width), height(height) {}

Ray Camera::getPixelRay(int x, int y) const {
	vec3d xDiff = (right_up_ - left_up_) * (double(x) / (width - 1));
	vec3d yDiff = (left_down_ - left_up_) * (double(y) / (height - 1));
	vec3d screen_position = left_up_ + xDiff + yDiff;
	Ray ray;
	ray.position = view_position_;
	ray.direction = screen_position - view_position_;
	return ray;
}

void Camera::setViewPosition(const vec3d &position) {
	view_position_ = position;
}

void Camera::setScreenCorners(const vec3d &left_up, const vec3d &right_up, const vec3d &left_down) {
	left_up_ = left_up;
	right_up_ = right_up;
	left_down_ = left_down;
}

void Camera::setByPositionDirection(const vec3d & position, const vec3d &direction, double Xsize, double Ysize, double focal_length) {
	vec3d base_normal(0, 0, 1);
	vec3d cameraX = direction.cross(base_normal).normalized();
	vec3d cameraY = direction.cross(cameraX).normalized();

	vec3d halfX = cameraX * 0.5 * Xsize;
	vec3d halfY = cameraY * 0.5 * Ysize;

	view_position_ = position - direction.normalized() * focal_length;
	left_up_ = position - halfX - halfY;
	left_down_ = position - halfX + halfY;
	right_up_ = position + halfX - halfY;
}