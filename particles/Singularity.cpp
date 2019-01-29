#include "Singularity.h"

Singularity::Singularity(vec3 sPos, GLuint _renderProgram, GLuint _transformProgram) {
	pos = sPos;
	vel = vec3(0.0f);
	radius = 0.2f;
	transformProgram = _transformProgram;
	particles = new Particle(2000, _renderProgram, _transformProgram, sPos, radius);
}
void Singularity::gravitate(const Singularity& target) {
	vec3 d = pos - target.pos;
	vec3 rot = normalize(cross(d, vec3(0.0, 0.0, 1.0)));
	//vel += 0.0000001f * rot;
	vel -= d * G / dot(d, d);
}
void Singularity::move() {
	vel *= 0.9999f;
	pos += vel;
	glUseProgram(transformProgram);
	GLint posLocation = glGetUniformLocation(transformProgram, "singularity");
	GLint radiusLocation = glGetUniformLocation(transformProgram, "radius");
	glUniform3f(posLocation, pos[0], pos[1], pos[2]);
	glUniform1f(radiusLocation, radius * radius);
	particles->doStuff();
}
void Singularity::collide(Singularity& target) {
	vec3 r = pos - target.pos;
	if (length(r) < radius + target.radius) {
		pos -= vel;
		vel *= -1.0f;
		target.pos -= target.vel;
		target.vel *= -1.0f;
	}
}