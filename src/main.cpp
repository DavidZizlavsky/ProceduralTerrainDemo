#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>

#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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

	Shader vertexShader = Shader(ReadShaderFromFile("shader/shader.vert"), GL_VERTEX_SHADER);
	Shader fragmentShader = Shader(ReadShaderFromFile("shader/shader.frag"), GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram = ShaderProgram(vertexShader, fragmentShader);
	shaderProgram.BindProgram();

	float vertices[] = {
		-0.2f, -0.2f, -0.2f,
		 0.2f, -0.2f, -0.2f,
		-0.2f,  0.2f, -0.2f,
		 0.2f,  0.2f, -0.2f,
		-0.2f, -0.2f,  0.2f,
		 0.2f, -0.2f,  0.2f,
		-0.2f,  0.2f,  0.2f,
		 0.2f,  0.2f,  0.2f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 3, 2,
		1, 5, 3,
		5, 7, 3,
		5, 4, 7,
		4, 6, 7,
		4, 0, 6,
		0, 2, 6,
		2, 3, 6,
		3, 7, 6,
		5, 4, 1,
		4, 0, 1
	};

	VertexBuffer vertexBuffer = VertexBuffer(vertices, sizeof(vertices) / sizeof(float));
	IndexBuffer indexBuffer = IndexBuffer(indices, sizeof(indices) / sizeof(unsigned int));
	Mesh mesh1 = Mesh(&vertexBuffer, &indexBuffer, &shaderProgram);

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
	Mesh mesh2 = Mesh(&vertexBuffer2, &indexBuffer2, &shaderProgram);

	int fbWidth, fbHeight;
	glClearColor(0.4f, 0.3f, 0.8f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetFramebufferSize(window, &fbWidth, &fbHeight); // TODO: move into callback, make fb struct, make fb struct global instance
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(45.0f * (float)glfwGetTime()),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.0f, 0.0f, 3.0f),  // camera position
			glm::vec3(0.0f, 0.0f, 0.0f),  // target point
			glm::vec3(0.0f, 1.0f, 0.0f)   // up vector
		);

		glm::mat4 projection = glm::perspective(
			glm::radians(45.0f),
			(float)fbWidth / fbHeight,
			0.1f,
			100.0f
		);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

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