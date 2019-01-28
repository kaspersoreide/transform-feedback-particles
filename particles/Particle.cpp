#include "Particle.h"

float random(float min, float max) {
	float n = (float)(std::rand() % 1000) / 1000;
	return n * (max - min) + min;
}

Particle::Particle(int n, GLuint _renderProgram, GLuint _transformProgram) {
	particleCount = n;
	renderProgram = _renderProgram;
	transformProgram = _transformProgram;

	std::vector<float> bufferData;
	for (int i = 0; i < n; i++) {
		//position
		bufferData.push_back(random(-1.0, 1.0));
		bufferData.push_back(random(-1.0, 1.0));
		bufferData.push_back(random(-1.0, 1.0));
		//velocity
		bufferData.push_back(0.0f);
		bufferData.push_back(0.0f);
		bufferData.push_back(0.0f);
		//color
		bufferData.push_back(random(0.0, 1.0) / 4);
		bufferData.push_back(random(0.0, 1.0) / 2);
		bufferData.push_back(random(0.0, 1.0));
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glCreateBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferData.size(), &bufferData[0], GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,							//position
		3,							//size
		GL_FLOAT,					//type
		GL_FALSE,					//normalize?
		9 * sizeof(float),			//stride (in bytes)
		0							//offset
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,							//position
		3,							//size
		GL_FLOAT,					//type
		GL_FALSE,					//normalize?
		9 * sizeof(float),			//stride (in bytes)
		(void*)(3 * sizeof(float))	//offset
	);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,							//position
		3,							//size
		GL_FLOAT,					//type
		GL_FALSE,					//normalize?
		9 * sizeof(float),			//stride (in bytes)
		(void*)(6 * sizeof(float))	//offset
	);

	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferData.size(), nullptr, GL_DYNAMIC_DRAW);
}


void Particle::doStuff(){
	glUseProgram(transformProgram);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glEnable(GL_RASTERIZER_DISCARD);
	//glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, TBO);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, TBO);
	glBeginTransformFeedback(GL_POINTS);
	glDrawArrays(GL_POINTS, 0, particleCount);
	glEndTransformFeedback();

	glUseProgram(renderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDisable(GL_RASTERIZER_DISCARD);
	glDrawArrays(GL_POINTS, 0, particleCount);

	GLuint temp = TBO;
	TBO = VAO;
	VAO = temp;
}