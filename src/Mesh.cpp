#include "Mesh.h"
#include <iostream>

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, ShaderProgram* shaderProgram)
{
	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
	this->shaderProgram = shaderProgram;
}

void Mesh::DrawMesh()
{
	this->vertexBuffer->BindBuffer();
	this->indexBuffer->BindBuffer();
	this->shaderProgram->BindProgram();
	SetUniforms();
	glDrawElements(GL_TRIANGLES, sizeof(unsigned int) * this->indexBuffer->GetDataCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::SetModelMatrix(glm::mat4 newModelMatrix)
{
	this->modelMatrix = newModelMatrix;
}

glm::mat4 Mesh::GetModelMatrix() const
{
	return this->modelMatrix;
}

void Mesh::SetUniforms()
{
	GLint uniformLocation = glGetUniformLocation(this->shaderProgram->GetShaderProgramId(), "model");
	if (uniformLocation == -1) {
		// Maybe throw an error here?
		std::cerr << "Locating 'Model' matrix uniform failed!" << std::endl;
		return;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));
}