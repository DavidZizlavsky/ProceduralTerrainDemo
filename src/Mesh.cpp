#include "Mesh.h"

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
	glDrawElements(GL_TRIANGLES, sizeof(unsigned int) * this->indexBuffer->GetDataCount(), GL_UNSIGNED_INT, nullptr);
}