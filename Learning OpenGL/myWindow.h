#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

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
	GLfloat* getCamera();

	~myWindow();
private:
	//void adjustViewport(GLFWwindow* window, int width, int height);
	GLFWwindow* mainWindow;
	int width, height, bwidth, bheight;
	float lastX, lastY, xChange, yChange;
	bool mouseFirstMoved;
	glm::mat4 camera;

	static void mouseMove(GLFWwindow* window, double xPos, double yPos);
};