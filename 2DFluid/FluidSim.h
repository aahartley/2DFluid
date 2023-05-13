#pragma once
#include "Window.h"
#include "Particle.h"
#include "Fluid.h"
#include "Constants.h"
#include <chrono>
#include <thread>

class FluidSim {
public:
	FluidSim();
	~FluidSim();
	int init();
	void run();
	void input();
	void update();
	void render();
	Vec2f cartesiantoScreen(const Vec2f& v);

	float dt = 0.00000000016f;

	Fluid* fluid;
private:
	Window* window;
};


