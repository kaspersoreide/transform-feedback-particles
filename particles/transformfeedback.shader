#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inVel;
layout(location = 2) in vec3 inColor;

out vec3 outPos;
out vec3 outVel;
out vec3 outColor;

uniform vec3 singularity;
uniform float radius;

void main() {
	vec3 vel = inVel;
	vec3 pos = inPos;
	vec3 d = singularity - inPos;
	if (dot(d, d) < radius && dot(vel, d) > 0.0) {
		pos -= vel;
		vel *= -1.0;
	}
	else {
		vel += 0.00001 * d / dot(d, d);
		vel *= 0.9999;
	}
	outVel = vel;
	outPos = inPos + vel;
	outColor = normalize(cross(inPos, inVel));
}