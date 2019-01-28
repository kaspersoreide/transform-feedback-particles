#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inVel;
layout(location = 2) in vec3 inColor;

out vec3 outPos;
out vec3 outVel;
out vec3 outColor;

void main() {
	float dist2 = dot(inPos, inPos);
	vec3 rot = normalize(cross(inPos, vec3(0.0, 0.0, 1.0)));
	vec3 vel = inVel + 0.0000001 * rot;
	vel -= 0.000001 * inPos / dist2;
	if (dist2 < 0.5) {
		//vel -= vel * 2 * dot(vel, normalize(inPos));
	}
	vel *= 0.9999;
	outVel = vel;
	outPos = inPos + vel;
	outColor = inColor;
}