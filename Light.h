#pragma once
#include "vec3d.h"

class Light {
private:
	vec3d position;
	double power_;
public:
	Light();
	Light(const vec3d &position, double power);
	vec3d getPosition() const;
	double getPower() const;
};