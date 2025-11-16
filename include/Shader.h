#pragma once
#include <GLEW/glew.h>
#include <string>

class Shader {
private:
	char* shaderSource = nullptr;
	GLuint shaderId = 0;
	GLenum shaderType = 0;
public:
	Shader(char* shaderSource, GLenum shaderType);
	GLuint GetShaderId();
};

char* ReadShaderFromFile(std::string filepath);