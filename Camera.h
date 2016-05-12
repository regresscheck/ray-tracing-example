#pragma once
#include "vec3d.h"
#include "Ray.h"

class Camera {
private:
	vec3d view_position_;
	vec3d left_up_, right_up_, left_down_;
	int width, height;
public:
	Camera();
	Camera(int width, int height);
	Ray getPixelRay(int, int) const;
	void setViewPosition(const vec3d &);
	void setScreenCorners(const vec3d &, const vec3d &, const vec3d &);
	void setByPositionDirection(const vec3d &, const vec3d &, double, double, double);
};