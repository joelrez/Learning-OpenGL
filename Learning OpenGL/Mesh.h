#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class Mesh
{
public:
	Mesh();
	
	void createMesh(float* vertices, int verticesSize);
	void renderMesh();

	~Mesh();
private:
	unsigned int VAO, VBO, shaderProgram;
};

