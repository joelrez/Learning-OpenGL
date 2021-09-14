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

std::string vFilePath = "vertex.vert", fFilePath = "fragment.frag";

const float toRadians = 3.14159265f / 180.0f;

std::string readFile(std::string filePath) {
	std::ifstream newFile(filePath);

	if (newFile.is_open()) {
		std::string code, line;
		while (!newFile.eof()) {
			getline(newFile, line);
			code.append(line + "\n");
		}
		newFile.close();
		return code.c_str();
	}
	else {
		printf("File '%s' could not be opened!", filePath.c_str());
		return "";
	}
}

int main() {

	myWindow window = myWindow();

	if (!window.Initialize("LearnOpenGL")) {
		return EXIT_FAILURE;
	}

	std::string vShaderCode = readFile(vFilePath), fShaderCode = readFile(fFilePath);
	const char* vShaderCode2 = vShaderCode.c_str();
	const char* fShadercode2 = fShaderCode.c_str();

	unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode2, NULL);
	glCompileShader(vShader);

	int success;
	char eLog[1024] = { 0 };
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShadercode2, NULL);
	glCompileShader(fShader);

	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int uniformModel = glGetUniformLocation(shaderProgram, "model");

	float vertices[] = {
		//Position				//Color
		-1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,		0.0f, 0.0f, 1.0f
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	float degree = 0.0f, deltadegree = 0.01f, scale = -1.0f, deltascale = 0.0001f;

	while (!window.WindowShouldClose()) {
		glfwPollEvents();
		window.processInput();

		glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render shapes

		glm::mat4 model(1.0f);
		model = glm::scale(model, glm::vec3(abs(scale), abs(scale), 1.0f));
		model = glm::rotate(model, degree * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		window.SwapBuffers();

		degree += deltadegree;
		if (degree >= 360.0f) {
			degree = 0.0f;
		}

		scale += deltascale;
		if (scale >= 1.0f) {
			scale *= -1.0f;
		}
	}

	glDeleteShader(fShader);
	glDeleteShader(vShader);
	glfwTerminate();
	return EXIT_SUCCESS;
}