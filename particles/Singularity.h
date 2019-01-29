#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Particle.h"

using namespace glm;

class Singularity {
public:
	Singularity(vec3 sPos, GLuint _renderProgram, GLuint _transformProgram);
	void gravitate(const Singularity& target);
	void collide(Singularity& target);
	void move();
protected:
	GLuint transformProgram;
	vec3 pos, vel;
	Particle* particles;
	float radius;
	const float G = 0.000001;
};