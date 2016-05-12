#include "Renderer.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace System::Collections::Generic;

RendererTask::RendererTask(int width, int height, std::vector<std::vector<Color>> &data, const Model &model, const Camera &camera, const std::vector<Light> &lights, int startIndex, int endIndex) :
	startIndex(startIndex), endIndex(endIndex), model(model), camera(camera), lights(lights), data(data),
	width(width), height(height) {}
void RendererTask::start() {
	for (int i = startIndex; i < endIndex; ++i) {
		int x = i / width;
		int y = i % width;
		renderPixel(x, y);
	}
}

void RendererTask::renderPixel(int x, int y) {
	Ray ray = camera.getPixelRay(x, y);
	IntersectionInfo info = model.intersect(ray);
	if (info.intersects()) {
		double brightness = calculateBrighness(info.getIntersectionPoint(), info.getNormal(), ray.direction, lights);
		data[x][y] = info.getMaterial().ambient * brightness;
	}
	else
		data[x][y] = Color(0, 0, 0);
}

double RendererTask::calculateBrighness(const vec3d &point, const vec3d &normal, const vec3d &direction, const std::vector<Light> &lights) {
	double brightness = 0.02;
	for (const Light & light : lights) {
		if (light.getPosition().getSqrDistance(point) < 1e-3)
			return 1.0;
		IntersectionInfo info = model.intersect(Ray(point, light.getPosition() - point));
		if (!info.intersects() || point.getSqrDistance(light.getPosition()) < point.getSqrDistance(info.getIntersectionPoint()))
			brightness += std::max(0.0, light.getPower() * normal.cos(light.getPosition() - point) / light.getPosition().getSqrDistance(point));
	}
	return std::min(1.0, brightness);
}

Renderer::Renderer(int width, int height) : width(width), height(height) {
	data.assign(width, std::vector<Color>(height));
}
Color Renderer::getPixel(int x, int y) const {
	return data[x][y];
}

void Renderer::setCamera(const Camera &new_camera) {
	camera = new_camera;
}

void Renderer::setModel(Model && new_model) {
	model = std::move(new_model);
}

void Renderer::setLights(const std::vector<Light> &new_lights) {
	lights = new_lights;
}

void Renderer::applyAntialiasing() {
	std::vector<std::vector<Color>> new_data;
	new_data.assign(width, std::vector<Color>(height));
	for (int x = 0; x < width; ++x)
		for (int y = 0; y < height; ++y) {
			Color sum(0, 0, 0);
			int cnt = 0;
			for (int dx = -1; dx <= 1; ++dx)
				for (int dy = -1; dy <= 1; ++dy)
					if (x + dx >= 0 && x + dx < width &&
						y + dy >= 0 && y + dy < height) {
						if (dx == 0 && dy == 0)
							cnt += 10, sum += data[x][y] * 10;
						else {
							++cnt;
							sum += data[x + dx][y + dy];
						}
					}
			new_data[x][y] = sum * (1.0 / cnt);
		}
	data = new_data;
}

void Renderer::render() {
	int maxIndex = width * height;
	const int kThreadsCount = 4;
	int step = maxIndex / kThreadsCount;
	int startIndex, endIndex = 0;
	List<Thread^>^ threads = gcnew List<Thread^>();
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	for (int i = 0; i < kThreadsCount; ++i) {
		startIndex = endIndex;
		endIndex += step;
		if (i + 1 == kThreadsCount)
			endIndex = maxIndex;
		RendererTask^ task = gcnew RendererTask(width, height, data, model, camera, lights, startIndex, endIndex);
		Thread^ thread = gcnew Thread(gcnew ThreadStart(task, &RendererTask::start));
		thread->Start();
		threads->Add(thread);
	}
	for each(Thread^ thread in threads) {
		thread->Join();
	}
	applyAntialiasing();
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time: " << elapsed_seconds.count() << std::endl;
}
