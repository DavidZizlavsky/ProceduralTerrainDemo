#include "Mesh.h"

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
{
	this->vertexBuffer = vertexBuffer;
	this->indexBuffer = indexBuffer;
}

void Mesh::DrawMesh()
{
	this->vertexBuffer->BindBuffer();
	this->indexBuffer->BindBuffer();
	glDrawElements(GL_TRIANGLES, sizeof(unsigned int) * this->indexBuffer->GetDataCount(), GL_UNSIGNED_INT, nullptr);
}