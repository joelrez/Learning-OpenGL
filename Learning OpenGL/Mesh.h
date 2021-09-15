#pragma once
#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "stb_image.h"

class Mesh
{
public:
	Mesh();
	
	void createMesh(float* vertices, int numOfVertexIndices, int sizeOfVertices,
					int* indices, int lenIndices);
	void renderMesh();

	~Mesh();
private:
	unsigned int VAO, VBO, EBO, shaderProgram, texture;
	int lenVertices, lenIndices;
};

