#include "Camera.h"

Camera::Camera(float s_fov) {
	FoV = s_fov;
	sight_direction = glm::vec3(0, 0, 1);
	cameraPosition = glm::vec3(0, 0, -1);
	upVector = glm::vec3(0, 1, 0); 

	momentum = glm::vec3(0.0f);
	angular_momentum = glm::vec3(0.0f);

	movAmount = 0.00005f;
	rotAmount = 0.00004f;
}

glm::vec3 Camera::getUpVector() {
	return upVector;
}

glm::vec3 Camera::getPosition() {
	return cameraPosition;
}

glm::vec3 Camera::getSightDirection() {
	return sight_direction;
}

void Camera::rotate(float dt) {
	if (rot[0]) angular_momentum += rotAmount * sight_direction;
	if (rot[1]) angular_momentum -= rotAmount * sight_direction;
	if (rot[2]) angular_momentum += rotAmount * upVector;
	if (rot[3]) angular_momentum -= rotAmount * upVector;
	glm::vec3 cp = glm::cross(sight_direction, upVector);
	if (rot[4]) angular_momentum += rotAmount * cp;
	if (rot[5]) angular_momentum -= rotAmount * cp;
	float radians = glm::length(angular_momentum);
	if (radians != 0.0) {
		upVector = glm::rotate(upVector, radians, angular_momentum);
		sight_direction = glm::rotate(sight_direction, radians, angular_momentum);
	}
	angular_momentum *= 0.99f;
}

void Camera::move(float dt) {
	if (mov[0]) momentum += movAmount * sight_direction;
	if (mov[1]) momentum -= movAmount * sight_direction;
	glm::vec3 cp = glm::cross(sight_direction, upVector);
	if (mov[2]) momentum -= movAmount * cp;
	if (mov[3]) momentum += movAmount * cp;
	if (mov[4]) momentum += movAmount * upVector;
	if (mov[5]) momentum -= movAmount * upVector;

	cameraPosition += momentum;
	momentum *= 0.999f;
}