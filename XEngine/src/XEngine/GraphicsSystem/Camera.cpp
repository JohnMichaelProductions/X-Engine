#include "Xpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/GraphicsSystem/Camera.h"
namespace XEngine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) : cameraProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), cameraViewMatrix(1.0f)
		{ cameraViewProjectionMatrix = cameraProjectionMatrix * cameraViewMatrix; }
	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top)
	{
		cameraProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		cameraViewProjectionMatrix = cameraProjectionMatrix * cameraViewMatrix;
	}
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), cameraPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(cameraRotation), glm::vec3(0, 0, 1));
		cameraViewMatrix = glm::inverse(transform);
		cameraViewProjectionMatrix = cameraProjectionMatrix * cameraViewMatrix;
	}
}