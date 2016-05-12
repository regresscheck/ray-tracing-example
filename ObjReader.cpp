#include "ObjReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include "Surface.h"


Model ObjReader::readFromFile(const char * filename) {
	std::ifstream in(filename);
	std::string type;
	std::map<std::string, Material> materials;
	std::vector<vec3d> vertices;
	std::vector<vec3d> vertex_normals;
	std::vector<Surface> surfaces;
	Material current;
	while (in >> type) {
		if (type == "mtllib") {
			char material_filename[250];
			in >> material_filename;
			auto new_materials = readMaterials(material_filename);
			materials.insert(new_materials.begin(), new_materials.end());
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "v") {
			vec3d vertex;
			in >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "vn") {
			vec3d normal;
			in >> normal.x >> normal.y >> normal.z;
			vertex_normals.push_back(normal);
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "vt") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "f") {
			Surface surface;
			surface.material = current;
			std::string line, temp;
			std::getline(in, line);
			std::istringstream iss(line);
			while (iss >> temp) {
				size_t current_pos = 0;
				size_t vertex_num = 0;
				while (current_pos < temp.size() && temp[current_pos] != '/') {
					vertex_num *= 10;
					vertex_num += temp[current_pos] - '0';
					++current_pos;
				}
				++current_pos;
				size_t texture_vertex_num = 0;
				while (current_pos < temp.size() && temp[current_pos] != '/') {
					texture_vertex_num *= 10;
					texture_vertex_num += temp[current_pos] - '0';
					++current_pos;
				}
				size_t normal_num = 0;
				++current_pos;
				while (current_pos < temp.size()) {
					normal_num *= 10;
					normal_num += temp[current_pos] - '0';
					++current_pos;
				}
				if (vertex_num < 0 || vertex_num > vertices.size()) {
					std::cerr << "WRONG VERTEX INDEX: " << vertex_num << std::endl;
					return Model();
				}
				if (normal_num < 0 || normal_num > vertex_normals.size()) {
					std::cerr << "WRONG NORMAL INDEX: " << normal_num << std::endl;
					return Model();
				}
				if (vertex_num != 0)
					surface.vertices.push_back(vertices[vertex_num - 1]);
				//surface.texture_vertices[i] = ;
				if (normal_num != 0)
					surface.vertex_normals.push_back(vertex_normals[normal_num - 1]);
			}
			surfaces.push_back(surface);
		}
		else if (type == "g") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "usemtl") {
			std::string material_name;
			in >> material_name;
			if (materials.count(material_name) == 0) {
				std::cerr << "NO MATERIAL FOUND: " << material_name << std::endl;
			}
			else
				current = materials[material_name];
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "s") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type == "o") {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (type.size() > 0 && type[0] == '#') {
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cerr << "WRONG FORMAT: " << type << std::endl;
			return Model();
		}
	}
	in.close();
	std::cout << "MODEL TRIANGLES: " << surfaces.size() << std::endl;
	return Model(surfaces);
}

std::map<std::string, Material> ObjReader::readMaterials(const char * filename) {
	std::map<std::string, Material> materials;
	std::ifstream in(filename);
	if (in.fail()) {
		std::cerr << "NO SUCH MATERIAL FILE: " << filename << std::endl;
		return materials;
	}
	std::string type;
	Material current;
	std::string material_name = "";
	while (in >> type) {
		if (type == "newmtl") {
			if (material_name != "")
				materials[material_name] = current;
			in >> material_name;
			current = Material();
		}
		else if (type == "Ka") {
			in >> current.ambient.r >> current.ambient.g >> current.ambient.b;
		}
		else if (type == "Kd") {
			in >> current.diffusive.r >> current.diffusive.g >> current.diffusive.b;
		}
		else if (type == "Ks") {
			in >> current.specular.r >> current.specular.g >> current.specular.b;
		}
		else if (type == "d" || type == "Tr") {
			in >> current.transparency;
		}
		else if (type == "Ns") {
			in >> current.specularity;
		}
		else if (type == "illum") {
		}
		else if (type.size() > 0 && type[0] == '#') {

		}
		else {
			std::cerr << "WRONG MATERIAL FILE: " << type << std::endl;
		}
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	in.close();
	if (material_name != "")
		materials[material_name] = current;
	return materials;
}