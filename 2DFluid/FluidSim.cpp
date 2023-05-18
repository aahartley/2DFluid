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
		std::cout << mx << ' ' << my << '\n';
		fluid->addQuantity(mx, my, 1000);
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

		//draw walls
		glColor4f(1, 0, 0, 1);
		glBegin(GL_POINTS);
		for (int y = 0; y < 512; y++) {
			for (int x = 0;x <512; x++) {
				if (x <= 2 || y <= 2|| x >= N - 3 || y >= N - 3) {
					//glVertex2f(x, y);

				}
			}
		}
		glEnd();

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
		for (int y = 3; y < N - 3; y++) {
			for (int x = 3; x < N - 3; x++) {
				float d = fluid->density[index(x, y)];
				if (d >= 1000.1f ) {
					glVertex2f(x, y);

				}
			}
		}
		glEnd();
	//}
	
}
void FluidSim::run() {
	//fluid->addQuantity(255, 255, 1000);
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