#pragma once
#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh {
private:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
public:
	Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
	void DrawMesh();
};