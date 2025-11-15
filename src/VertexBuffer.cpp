#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float* vertices, unsigned int verticesCount)
{
	this->vertices = vertices;
	this->verticesCount = verticesCount;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	this->BindBuffer();

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->verticesCount, this->vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void VertexBuffer::BindBuffer()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}