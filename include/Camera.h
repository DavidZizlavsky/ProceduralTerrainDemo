#pragma once
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Structs.h"
#include "ShaderProgram.h"

class Camera {
private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	Size viewportSize = { 0,0 };

	void RecalculateMatrices();
public:
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	void SetViewportSize(Size newViewportSize);
	bool SetUniforms(ShaderProgram shaderProgram);
	Camera() {};
	Camera(Size initialViewportSize);
};