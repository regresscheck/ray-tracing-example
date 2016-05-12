#pragma once
#include "Model.h"
#include "Material.h"
#include <map>
#include <string>

class Model;

class ObjReader {
private:
	static std::map<std::string, Material> readMaterials(const char *);
public:
	static Model readFromFile(const char *);
};