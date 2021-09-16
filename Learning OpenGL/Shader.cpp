#include "Shader.h"

Shader::Shader() {

}

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

bool Shader::createShaderProgram(std::string vertFilePath, std::string fragFilePath) {
	std::string vShaderCode = readFile(vertFilePath), fShaderCode = readFile(fragFilePath);
	const char* vShaderCode2 = vShaderCode.c_str();
	const char* fShadercode2 = fShaderCode.c_str();

	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vShaderCode2, NULL);
	glCompileShader(vShader);

	int success;
	char eLog[1024] = { 0 };
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShader, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return false;
	}

	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fShadercode2, NULL);
	glCompileShader(fShader);

	glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShader, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return false;
	}

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, eLog);
		std::cout << eLog << std::endl;
		return false;
	}

	uniformModel = glGetUniformLocation(shaderProgram, "model");
	uniformProjection = glGetUniformLocation(shaderProgram, "projection");

	return true;
}

unsigned int Shader::getUniformModelLocation() {
	return uniformModel;
}

unsigned int Shader::getUniformProjectionLocation() {
	return uniformProjection;
}

void Shader::runProgram() {
	glUseProgram(shaderProgram);
}

void Shader::deleteShaders() {
	glDeleteShader(fShader);
	glDeleteShader(vShader);
}

Shader::~Shader() {

}