#include "Camera.h"

Camera::Camera(){}

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) {
	this->pos = pos;
	this->up = up;
	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

void Camera::translate(glm::vec3 move) {
	this->pos += move;
}

void Camera::update() {
	target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	target.y = sin(glm::radians(pitch));
	target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	target = glm::normalize(target);

	view = glm::lookAt(pos, pos + target, up);
}

void Camera::rotate(float deltayaw, float deltapitch) {
	yaw += deltayaw;
	pitch += deltapitch;

	if (pitch > 89.0f) 
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
}

GLfloat* Camera::getCamera() {
	update();
	return glm::value_ptr(view);
}

Camera::~Camera() {

}