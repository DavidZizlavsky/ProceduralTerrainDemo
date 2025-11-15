#pragma once
#include <GLEW/glew.h>

class IndexBuffer {
private:
	unsigned int* indices = nullptr;
	unsigned int indicesCount = 0;
	GLuint ibo = 0;
public:
	IndexBuffer(unsigned int* indices, unsigned int indicesCount);
	void BindBuffer();
	unsigned int GetDataCount();
	~IndexBuffer();
};