#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

class myWindow
{
public:
	myWindow();
	myWindow(int width, int height);

	int Initialize(const char* windowTitle);
	void processInput();
	bool WindowShouldClose();
	float getAspectRatio();
	void SwapBuffers();

	~myWindow();
private:
	//void adjustViewport(GLFWwindow* window, int width, int height);
	GLFWwindow* mainWindow;
	int width, height, bwidth, bheight;
};