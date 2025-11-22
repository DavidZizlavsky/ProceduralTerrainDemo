#pragma once
#include <GLEW/glew.h>
#include <glm/matrix.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Mesh {
private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ShaderProgram* shaderProgram = nullptr;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
public:
	Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, ShaderProgram* shaderProgram);
	void SetModelMatrix(glm::mat4 newModelMatrix);
	glm::mat4 GetModelMatrix() const;
	void DrawMesh();
};