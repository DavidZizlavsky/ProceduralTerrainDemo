#pragma once
#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class Mesh {
private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	ShaderProgram* shaderProgram = nullptr;
public:
	Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, ShaderProgram* shaderProgram);
	void DrawMesh();
};