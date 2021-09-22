#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Camera.h"

class myWindow
{
public:
	myWindow();
	myWindow(int width, int height, int inv);

	int Initialize(const char* windowTitle);
	void processInput();
	bool WindowShouldClose();
	float getAspectRatio();
	void SwapBuffers();
	GLfloat* getCamera();

	~myWindow();
private:
	//void adjustViewport(GLFWwindow* window, int width, int height);
	GLFWwindow* mainWindow;
	int width, height, bwidth, bheight, inv;
	float lastX, lastY;
	bool mouseFirstMoved;
	Camera camera;

	static void mouseMove(GLFWwindow* window, double xPos, double yPos);
};