#include "loadShaders.h"

GLuint loadShaders() {
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();
	//Create shaders and shader program
	{
		std::ifstream source_file("vertex.shader");

		std::string data;
		std::getline(source_file, data, '\0');

		const GLchar* vshader_source(data.c_str());
		
		glShaderSource(vshader, 1, &vshader_source, NULL);
	}
	{
		std::ifstream source_file("fragment.shader");

		std::string data;
		std::getline(source_file, data, '\0');

		const GLchar *fshader_source(data.c_str());

		glShaderSource(fshader, 1, &fshader_source, NULL);
	}

	glCompileShader(vshader);
	glCompileShader(fshader);

	glAttachShader(program, vshader);
	glAttachShader(program, fshader);

	glLinkProgram(program);

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << error << "\n";
	}

	return program;
}

GLuint loadTransformShader() {
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint program = glCreateProgram();
	//Create shaders and shader program
	{
		std::ifstream source_file("transformfeedback.shader");

		std::string data;
		std::getline(source_file, data, '\0');

		const GLchar* vshader_source(data.c_str());

		glShaderSource(vshader, 1, &vshader_source, NULL);
	}

	glCompileShader(vshader);

	glAttachShader(program, vshader);

	const GLchar* feedbackVaryings[] = { "outPos", "outVel", "outColor" };
	glTransformFeedbackVaryings(program, 3, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(program);

	glDeleteShader(vshader);

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << error << "\n";
	}

	return program;
}