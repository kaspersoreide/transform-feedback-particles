#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vel;
layout(location = 2) in vec3 color;
					 
out vec3 theColor;

uniform mat4 ViewProjection;

void main() {
	gl_Position = ViewProjection * vec4(pos, 1.0);
	theColor = color;
}