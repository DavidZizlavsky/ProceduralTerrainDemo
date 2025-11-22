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
#include "Camera.h"

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

Camera camera;

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

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Procedural terrain DEMO", nullptr, nullptr);
	if (!window) {
		std::cerr << "GLFW failed to create a window!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	int framebufferWidth, framebufferHeight;
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	camera = Camera({ framebufferWidth, framebufferHeight });
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

	glClearColor(0.35f, 0.55f, 0.75f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(45.0f * (float)glfwGetTime()),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		mesh1.SetModelMatrix(model);

		model = glm::rotate(
			glm::mat4(1.0f),
			glm::radians(45.0f * (float)glfwGetTime()),
			glm::vec3(0.0f, -1.0f, 0.0f)
		);
		mesh2.SetModelMatrix(model);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(mesh1.GetModelMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "view"), 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.GetProjectionMatrix()));

		mesh1.DrawMesh();

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.GetShaderProgramId(), "model"), 1, GL_FALSE, glm::value_ptr(mesh2.GetModelMatrix()));
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
	camera.SetViewportSize({ width, height });
}