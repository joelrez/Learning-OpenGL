#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <math.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch);

	GLfloat* getCamera();
	void translate(glm::vec3 move);
	void rotate(float deltayaw, float deltapitch);

	~Camera();
private:
	glm::mat4 view;
	glm::vec3 pos, up, target;
	float yaw, pitch;
	int inverted;
	void update();
};