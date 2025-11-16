#pragma once
#include <GLEW/glew.h>
#include "Shader.h"

class ShaderProgram {
private:
	GLuint shaderProgramId = 0;
public:
	ShaderProgram(Shader& vertexShader, Shader& fragmentShader);
	void BindProgram();
};