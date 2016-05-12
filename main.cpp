#using <system.drawing.dll>
#include "Renderer.h"
#include "Model.h"
#include "Light.h"
#include <iostream>

using namespace System;

const int WIDTH = 500;
const int HEIGHT = 500;

int main() {
	Drawing::Bitmap^ bitmap = gcnew Drawing::Bitmap(WIDTH, HEIGHT);
	Renderer renderer(WIDTH, HEIGHT);
	Camera camera(WIDTH, HEIGHT);
	camera.setByPositionDirection(vec3d(5000, 5000, 5000), vec3d(-1, -1, -1), 10, 10, 10);
	Model model = Model::readFromObj("./Rotunda.obj");

	if (!model.initialized())
		return 1;

	std::vector<Light> lights;
	lights.push_back(Light(vec3d(20000, 50000, 50000), 4000000000.0));
	
	renderer.setModel(std::move(model));
	renderer.setCamera(camera);
	renderer.setLights(lights);
	renderer.render();
	for (int i = 0; i < WIDTH; ++i)
		for (int j = 0; j < HEIGHT; ++j)
			bitmap->SetPixel(i, j, renderer.getPixel(i, j));
	bitmap->Save("output.png");
}