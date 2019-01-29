#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

#include "Particle.h"
#include "loadShaders.h"
#include "Camera.h"
#include "Singularity.h"

using namespace std;

const int width = 1920;
const int height = 1080;
GLFWwindow* window;

Camera camera(1.2f);

bool key_w, key_a, key_s, key_d, key_q, key_e, key_up, key_down, key_left, key_right;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_E) {
		if (action == GLFW_PRESS) {
			camera.rot[0] = true;
			std::cout << "hei";
		}
		if (action == GLFW_RELEASE) camera.rot[0] = false;
	}
	if (key == GLFW_KEY_Q) {
		if (action == GLFW_PRESS) camera.rot[1] = true;
		if (action == GLFW_RELEASE) camera.rot[1] = false;
	}
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS) camera.rot[2] = true;
		if (action == GLFW_RELEASE) camera.rot[2] = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS) camera.rot[3] = true;
		if (action == GLFW_RELEASE) camera.rot[3] = false;
	}
	if (key == GLFW_KEY_UP) {
		if (action == GLFW_PRESS) camera.rot[4] = true;
		if (action == GLFW_RELEASE) camera.rot[4] = false;
	}
	if (key == GLFW_KEY_DOWN) {
		if (action == GLFW_PRESS) camera.rot[5] = true;
		if (action == GLFW_RELEASE) camera.rot[5] = false;
	}

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) camera.mov[0] = true;
		if (action == GLFW_RELEASE) camera.mov[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) camera.mov[1] = true;
		if (action == GLFW_RELEASE) camera.mov[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) camera.mov[2] = true;
		if (action == GLFW_RELEASE) camera.mov[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) camera.mov[3] = true;
		if (action == GLFW_RELEASE) camera.mov[3] = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) camera.mov[4] = true;
		if (action == GLFW_RELEASE) camera.mov[4] = false;
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		if (action == GLFW_PRESS) camera.mov[5] = true;
		if (action == GLFW_RELEASE) camera.mov[5] = false;
	}
}

int init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glPointSize(1.0f);
	glClearColor(0.0, 0.0, 0.0, 0.01);

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}
}

int main(void) {
	if (init() == -1) {
		return -1;
	}

	GLuint renderProgram = loadShaders();
	GLuint transformProgram = loadTransformShader();

	glm::mat4 Projection = glm::perspective(
		1.5f, 
		static_cast<float>(1),			//(float)width / height, 
		0.001f, 
		1000.0f
	);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, -3.0f),
		glm::vec3(0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	glm::mat4 ViewProjection = Projection * View;
	glUseProgram(renderProgram);
	GLint l_VP(glGetUniformLocation(renderProgram, "ViewProjection"));
	glUniformMatrix4fv(l_VP, 1, GL_FALSE, &ViewProjection[0][0]);

	//Particle p(10000, renderProgram, transformProgram);

	std::vector<Singularity*> voids;
	for (int i = 0; i < 50; i++) {
		vec3 pos(random(-20.0f, 20.0f), random(-20.0f, 20.0f), random(-20.0f, 20.0f));
		voids.push_back(new Singularity(pos, renderProgram, transformProgram));
	}

	int error = glGetError();
	
	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	glfwSetKeyCallback(window, keyCallback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (int i = 0; i < voids.size(); i++) {
			for (int j = 0; j < voids.size(); j++) {
				if (i == j) continue;
				voids[i]->gravitate(*voids[j]);
				voids[i]->collide(*voids[j]);
			}
			voids[i]->move();
		}

		camera.move(0.1f);
		camera.rotate(0.1f);

		View = glm::lookAt(
			camera.getPosition(),
			camera.getPosition() + camera.getSightDirection(),
			camera.getUpVector()
		);
		
		ViewProjection = Projection * View;
		l_VP = glGetUniformLocation(renderProgram, "ViewProjection");
		glUniformMatrix4fv(l_VP, 1, GL_FALSE, &ViewProjection[0][0]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}