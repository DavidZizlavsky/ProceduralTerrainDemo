#pragma once
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Structs.h"

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
	Camera() {};
	Camera(Size initialViewportSize);
};