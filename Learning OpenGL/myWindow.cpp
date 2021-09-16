#include "myWindow.h"

//Default constructor
myWindow::myWindow() {
	//Default dimensions of window
	this->width = 800;
	this->height = 600;
}

//Overloaded constructor
myWindow::myWindow(int width, int height) {
	//User-defined dimensions of window
	this->width = width;
	this->height = height;
}

float myWindow::getAspectRatio() {
	return (float)bwidth / (float)bheight;
}

void myWindow::processInput() {
	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(mainWindow, true);
	}

	glfwGetFramebufferSize(mainWindow, &bwidth, &bheight);
}

void adjustViewport(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool myWindow::WindowShouldClose() {
	return glfwWindowShouldClose(mainWindow);
}

void myWindow::SwapBuffers() {
	glfwSwapBuffers(mainWindow);
}

//Instantiate window with OpenGL constraints
int myWindow::Initialize(const char* windowTitle) {
	if (!glfwInit()) {
		printf("GLFW failed to initialize!");
		return 0;
	}

	//Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Restrict OpenGL to the Core - Doesn't allow backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Instantiate mainWindow 
	//3rd argument allows us to specify a monitor
	//GLFWmonitor* monitor = glfwGetPrimaryMonitor(); // To set the current monitor to the primary monitor
	mainWindow = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (!mainWindow) {
		printf("Window failed to be created");
		glfwTerminate();
		return 0;
	}

	//Set thread to work on this window
	glfwMakeContextCurrent(mainWindow);

	//Set GLEW to experimental mode meaning we can use newer features with pointer stuff.
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW failed to initialize!");
		glfwTerminate();
		return 0;
	}

	glfwGetFramebufferSize(mainWindow, &bwidth, &bheight);

	glViewport(0, 0, bwidth, bheight);

	glfwSetFramebufferSizeCallback(mainWindow, adjustViewport);

	return 1;
}

myWindow::~myWindow() {
	glfwTerminate();
}