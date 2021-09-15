#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "myWindow.h"
#include "Mesh.h"
#include "Shader.h"

std::string vFilePath = "vertex.vert", fFilePath = "fragment.frag";

const float toRadians = 3.14159265f / 180.0f;

int main() {

	myWindow window = myWindow();

	if (!window.Initialize("LearnOpenGL")) {
		return EXIT_FAILURE;
	}

	Shader* shader = new Shader();
	if (!shader->createShaderProgram(vFilePath, fFilePath)) {
		printf("Shader program failed to compile!");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	int sizeOfVertices = 8; //number of float values in each vertex
	float vertices[] = {
		//Position				//Color				//Texcoords
		-1.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 -1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 1.0f,  -1.0f, 0.0f,	0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f
	};

	// Compute the number of indices in the vertices array
	int lenVertices = sizeof(vertices) / (sizeOfVertices * sizeof(vertices[0]));

	// Specify vertices to draw
	int indices[] = {
		0,1,2,
		0,3,2
	};
	int lenIndices = sizeof(indices) / sizeof(int);

	// Create a mesh
	Mesh* triangle = new Mesh();
	triangle->createMesh(vertices, lenVertices, sizeOfVertices,
						 indices, lenIndices);

	float degree = 0.0f, deltadegree = 0.01f, scale = -1.0f, deltascale = 0.0001f;

	while (!window.WindowShouldClose()) {
		glfwPollEvents();
		window.processInput();

		glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render shapes
		shader->runProgram();
		unsigned int uniformModel = shader->getUniformModelLocation();

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(abs(scale), abs(scale), 1.0f));
		model = glm::rotate(model, degree * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		triangle->renderMesh();

		window.SwapBuffers();

		/*degree += deltadegree;
		if (degree >= 360.0f) {
			degree = 0.0f;
		}

		scale += deltascale;
		if (scale >= 1.0f) {
			scale *= -1.0f;
		}*/
	}
	
	glfwTerminate();
	return EXIT_SUCCESS;
}