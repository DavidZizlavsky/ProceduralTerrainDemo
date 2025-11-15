#pragma once
#include <GLEW/glew.h>

class VertexBuffer {
private:
	float* vertices = nullptr;
	unsigned int verticesCount = 0;
	GLuint vao = 0;
	GLuint vbo = 0;
public:
	VertexBuffer(float* vertices, unsigned int verticesCount);
	void BindBuffer();
	~VertexBuffer();
};