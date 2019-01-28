#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <vector>

using namespace glm;

float random(float min, float max);

class Particle {
public:
	Particle(int n, GLuint _renderProgram, GLuint _transformProgram);
	void doStuff();
protected:
	GLuint VBO, TBO, VAO, renderProgram, transformProgram;
	int particleCount;
};