#pragma once
#include <vector>
#include "Color.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

using namespace System;
using namespace System::Threading;

public ref class RendererTask {
private:
	int startIndex, endIndex;
	const Model & model;
	const std::vector<Light> & lights;
	const Camera & camera;
	std::vector<std::vector<Color>> & data;
	int width, height;
public:
	RendererTask(int width, int height, std::vector<std::vector<Color>> & data, const Model &, const Camera &, const std::vector<Light> &, int, int);
	void start();
	double calculateBrighness(const vec3d &, const vec3d &, const vec3d &, const std::vector<Light> &);
	void renderPixel(int, int);
};

class Renderer {
private:
	int width, height;
	Model model;
	Camera camera;
	std::vector<std::vector<Color>> data;
	std::vector<Light> lights;
	void applyAntialiasing();
public:
	Renderer(int, int);
	Color getPixel(int, int) const;
	void setCamera(const Camera &);
	void setModel(Model &&);
	void setLights(const std::vector<Light> &);
	void render();
};