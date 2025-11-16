#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(char* shaderSource, GLenum shaderType)
{
	this->shaderSource = shaderSource;
	this->shaderType = shaderType;

	this->shaderId = glCreateShader(this->shaderType);
	glShaderSource(this->shaderId, 1, &this->shaderSource, nullptr);
	glCompileShader(this->shaderId);
}

GLuint Shader::GetShaderId()
{
	return this->shaderId;
}

char* ReadShaderFromFile(std::string filepath)
{
	std::ifstream stream(filepath, std::ios::binary | std::ios::ate);

	if (!stream) {
		std::cerr << "Failed to open a file!" << std::endl;
		return nullptr;
	}

	std::streamsize fileCharCount = stream.tellg();
	stream.seekg(0, std::ios::beg);

	char* buffer = new char[fileCharCount + 1];

	if (!stream.read(buffer, fileCharCount)) {
		delete[] buffer;
		return nullptr;
	}

	buffer[fileCharCount] = '\0';
	return buffer;
}