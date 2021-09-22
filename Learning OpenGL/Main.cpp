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

int main() {

	myWindow window = myWindow(800, 600, 1);

	if (!window.Initialize("LearnOpenGL")) {
		return EXIT_FAILURE;
	}

	Shader* shader = new Shader();
	if (!shader->createShaderProgram(vFilePath, fFilePath)) {
		printf("Shader program failed to compile!");
		glfwTerminate();
		return EXIT_FAILURE;
	}

	int sizeOfVertices = 5; //number of float values in each vertex
	float vertices[] = {
		//Position				//Texcoords
		-0.5f, -0.5f,-0.5f,		0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f

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
	float dist = -3.0f, deltadist = -0.001;

	while (!window.WindowShouldClose()) {
		glfwPollEvents();
		window.processInput();

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//render shapes
		shader->runProgram();
		unsigned int uniformModel = shader->getUniformModelLocation();
		unsigned int uniformProjection = shader->getUniformProjectionLocation();
		unsigned int uniformView = shader->getUniformViewLocation();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(abs(scale), abs(scale), 1.0f));
		model = glm::rotate(model, glm::radians(degree), glm::vec3(0.0f, 1.0f, 0.0f));
		
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.getAspectRatio(), 0.1f, 100.0f);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, window.getCamera());

		triangle->renderMesh();

		window.SwapBuffers();

		//dist += deltadist;

		degree += deltadegree;
		if (degree >= 360.0f) {
			degree = 0.0f;
		}

		/*scale += deltascale;
		if (scale >= 1.0f) {
			scale *= -1.0f;
		}*/
	}
	
	glfwTerminate();
	return EXIT_SUCCESS;
}