#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "Mesh.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
std::string readFileContent(const std::string& filepath);

int main(int argc, char* argv[])
{
	if (!glfwInit()) {
		std::cerr << "GLFW initialization failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Procedural terrain DEMO", nullptr, nullptr);
	if (!window) {
		std::cerr << "GLFW failed to create a window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW initialization failed!" << std::endl;
		glfwTerminate();
		return -1;
	}

	float vertices[] = {
		-0.2f, -0.2f, 0.0f,
		 0.2f, -0.2f, 0.0f,
		-0.2f,  0.2f, 0.0f,
		 0.2f,  0.2f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2
	};

	VertexBuffer vertexBuffer = VertexBuffer(vertices, sizeof(vertices) / sizeof(float));
	IndexBuffer indexBuffer = IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));
	Mesh mesh1 = Mesh(&vertexBuffer, &indexBuffer);

	float vertices2[] = {
		-0.7f,  0.7f,  0.0f,
		-0.7f,  0.3f,  0.0f,
		-0.5f,  0.3f,  0.0f,
	};

	unsigned int indices2[] = {
		0, 1, 2
	};

	VertexBuffer vertexBuffer2 = VertexBuffer(vertices2, sizeof(vertices2) / sizeof(float));
	IndexBuffer indexBuffer2 = IndexBuffer(indices2, sizeof(indices2) / sizeof(unsigned int));
	Mesh mesh2 = Mesh(&vertexBuffer2, &indexBuffer2);

	std::string vertexShaderSourceString = readFileContent("shader/shader.vert");
	char* vertexShaderSource = vertexShaderSourceString.data();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	std::string fragmentShaderSourceString = readFileContent("shader/shader.frag");
	char* fragmentShaderSource = fragmentShaderSourceString.data();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glClearColor(0.4f, 0.3f, 0.8f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		mesh1.DrawMesh();
		mesh2.DrawMesh();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

std::string readFileContent(const std::string& filepath) {
	std::ifstream file(filepath, std::ios::binary);
	return { std::istreambuf_iterator<char>(file),
			 std::istreambuf_iterator<char>() };
}