#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(float s_fov);
	void rotate(float dt);
	void move(float dt);
	glm::vec3 getPosition();
	glm::vec3 getSightDirection();
	glm::vec3 getUpVector();

	glm::vec3 upVector;
	glm::vec3 sight_direction;
	bool mov[6];
	bool rot[6];
private:
	float rotAmount;
	float movAmount;
	float FoV;

	glm::vec3 cameraPosition;
	glm::mat4 View;
	glm::mat4 Model = glm::mat4(1.0f);
	glm::vec3 angular_momentum;
	glm::vec3 momentum;

};