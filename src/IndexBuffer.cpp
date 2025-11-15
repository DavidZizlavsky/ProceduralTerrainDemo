#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int indicesCount) 
{
	this->indices = indices;
	this->indicesCount = indicesCount;

	glGenBuffers(1, &ibo);
	
	this->BindBuffer();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* this->indicesCount, this->indices, GL_STATIC_DRAW);
}

void IndexBuffer::BindBuffer()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

unsigned int IndexBuffer::GetDataCount()
{
	return this->indicesCount;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ibo);
}