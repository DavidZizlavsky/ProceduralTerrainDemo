#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader)
{
	this->shaderProgramId = glCreateProgram();
	glAttachShader(this->shaderProgramId, vertexShader.GetShaderId());
	glAttachShader(this->shaderProgramId, fragmentShader.GetShaderId());
	glLinkProgram(this->shaderProgramId);
}

void ShaderProgram::BindProgram()
{
	glUseProgram(this->shaderProgramId);
}

GLuint ShaderProgram::GetShaderProgramId()
{
	return this->shaderProgramId;
}