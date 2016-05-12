#include "Light.h"

Light::Light() {};
Light::Light(const vec3d &position, double power) : position(position), power_(power) {};
vec3d Light::getPosition() const {
	return position;
}

double Light::getPower() const {
	return power_;
}