#include "Camera.h"
#include <iostream>

Camera::Camera(Size initialViewportSize)
{
	this->viewportSize = initialViewportSize;
	RecalculateMatrices();
}

glm::mat4 Camera::GetViewMatrix() const
{
	return this->view;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	return this->projection;
}

void Camera::SetViewportSize(Size newViewportSize)
{
	this->viewportSize = newViewportSize;
	RecalculateMatrices();
}

bool Camera::SetUniforms(ShaderProgram shaderProgram)
{
	GLint uniformLocation;
	
	uniformLocation = glGetUniformLocation(shaderProgram.GetShaderProgramId(), "view");
	if (uniformLocation == -1) {
		std::cerr << "Locating 'View' matrix uniform failed!" << std::endl;
		return false;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(GetViewMatrix()));

	uniformLocation = glGetUniformLocation(shaderProgram.GetShaderProgramId(), "projection");
	if (uniformLocation == -1) {
		std::cerr << "Locating 'Projection' matrix uniform failed!" << std::endl;
		return false;
	}
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(GetProjectionMatrix()));

	return true;
}

void Camera::RecalculateMatrices()
{
	if (viewportSize.x == 0 || viewportSize.y == 0) {
		std::cerr << "Incorrect viewport size! Recalculating camera matrices is not possible!" << std::endl;
		return;
	}

	this->view = glm::lookAt(
		glm::vec3(0.0f, 1.0f, 3.0f),  // camera position
		glm::vec3(0.0f, 0.0f, 0.0f),  // target point
		glm::vec3(0.0f, 1.0f, 0.0f)   // up vector
	);

	this->projection = glm::perspective(
		glm::radians(45.0f),
		(float)this->viewportSize.x / this->viewportSize.y,
		0.1f,
		100.0f
	);
}