#pragma once
#include "GLFW/glfw3.h"
#include "Constants.h"
#include <iostream>

class Window {
public:
	Window();
	~Window();

	GLFWwindow* getPointer();
	int init();
	void processInput(GLFWwindow* window);


private:
	GLFWwindow* window;


};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
