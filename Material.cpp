#include "Material.h"

Material::Material() {
	ambient.r = ambient.g = ambient.b = 1;
	diffusive.r = diffusive.g = diffusive.b = 1;
	specular.r = specular.g = specular.b = 1;
	transparency = 0;
	specularity = 0;
}