#pragma once

#include "Color.h"

class Material {
public:
	Color ambient, diffusive, specular;
	double transparency, specularity;
	Material();
};