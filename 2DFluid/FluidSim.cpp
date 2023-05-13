#include "FluidSim.h"

FluidSim::FluidSim() {
	window = new Window();
	fluid = new Fluid(dt, 0.4, 0);
}

FluidSim::~FluidSim() {
	delete window;
}

Vec2f FluidSim::cartesiantoScreen(const Vec2f& v) {
	return Vec2f{ originX + (v.x*unitLength), originY - (v.y*unitLength) };
}


int FluidSim::init() {
	return 0;
}
void FluidSim::input() {
	window->processInput(window->getPointer());
	if (clickD) {
		//add 
		fluid->addQuantity(200, 200, 100);

		clickD = false;
	}
	if (clickV) {
		clickV = false;
	}
}
void FluidSim::update() {
	fluid->advect();
}
void FluidSim::render(int n) {
//	if (n < 2) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw grid
	/*	glColor4f(1, 1, 1, 0.2);
		glBegin(GL_POINTS);
		for (int j = 0; j < 512; j++) {
			for (int i = 0; i <512; i++) {
				glVertex2f(i, j);
				glVertex2f(j, i);

			}
		}
		glEnd();*/

		glColor4f(1, 1, 1, 1);
		//glBegin(GL_QUADS);
		//for (int x = 0; x < N; x++) {
		//	for (int y = 0; y < N; y++) {
		//		float d = fluid->density[index(x, y)];
		//		if (d > 1000) {
		//			glVertex2f(x - 2, y - 2);
		//			glVertex2f(x + 2, y + 2);
		//			glVertex2f(x - 2, y + 2);
		//			glVertex2f(x + 2, y - 2);
		//		}
		//	}
		//}
		//glEnd();
		glBegin(GL_POINTS);
		for (int x = 1; x < N - 1; x++) {
			for (int y = 1; y < N - 1; y++) {
				float d = fluid->density[index(x, y)];
				if (d > 1000) {
					glVertex2f(x, y);

				}
			}
		}
		glEnd();
	//}
	
}
void FluidSim::run() {
	//fluid->addQuantity(256, 256, 100);
	int n = 1;
	while (!glfwWindowShouldClose(window->getPointer())) {
		input();

		update();
	
		render(n);
		n++;
		glfwSwapBuffers(window->getPointer());
		glfwPollEvents();

	}
	glfwTerminate();
}