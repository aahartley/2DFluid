#include "Window.h"

Window::Window() {
    init();
};
Window::~Window() {
};

int Window::init() {

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "Fluid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwSwapInterval(1);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (monitor->width - WINDOW_SIZE_X) / 2, (monitor->height - WINDOW_SIZE_Y) / 2);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glViewport(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    /* Pick 2D clipping window to match size of X window. This choice
    avoids having to scale object coordinates each time window is
    resized. */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)WINDOW_SIZE_X, (GLdouble)WINDOW_SIZE_Y, 0.0, -1.0, 1.0);

    /* set clear color to black and clear window */

    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    return 0;
}
void Window::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);
    //if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);
    //if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);
    //if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);

}

GLFWwindow* Window::getPointer() {
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    /* adjust clipping box */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble)width, (GLdouble)height,0.0 , -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* adjust viewport and clear */

    glViewport(0, 0, width, height);
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();


    //------ reset the window size
    WINDOW_SIZE_X = width;
    WINDOW_SIZE_Y = height;

    originX = WINDOW_SIZE_X / 2;
    originY = WINDOW_SIZE_Y / 2;

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        mx = static_cast<int>(xpos);
        my = static_cast<int>(ypos);
        clickD = true;
        //std::cout << mx << ' ' << my << '\n';

    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);
        mx = static_cast<int>(xpos);
        my = static_cast<int>(ypos);
        clickV = true;
        //std::cout << mx << ' ' << my << '\n';

    }
}