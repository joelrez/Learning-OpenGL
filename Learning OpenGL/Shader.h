#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Shader
{
public:
	Shader();

	bool createShaderProgram(std::string vertFilePath, std::string fragFilePath);
	void deleteShaders();
	unsigned int getUniformModelLocation();
	unsigned int getUniformProjectionLocation();
	void runProgram();

	~Shader();
private:
	unsigned int vShader, fShader, shaderProgram, uniformModel, uniformProjection;
};

