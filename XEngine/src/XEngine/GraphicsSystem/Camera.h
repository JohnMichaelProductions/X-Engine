#pragma once
#include <glm/glm.hpp>
namespace XEngine
{
	class OrthographicCamera
	{
	public:
		// Defined in Source File
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() {}
		// Prototype in Header File
		const glm::vec3 GetPosition() const
			{ return cameraPosition; }
		void SetPosition(const glm::vec3& position)
		{
			cameraPosition = position;
			RecalculateViewMatrix();
		}
		float GetRotation() const 
			{ return cameraRotation; }
		void SetRotation(float rotation)
		{
			cameraRotation = rotation; 
			RecalculateViewMatrix();
		}
		const glm::mat4& GetProjectionMatrix() const 
			{ return cameraProjectionMatrix; }
		void SetProjectionMatrix(float left, float right, float bottom, float top);
		const glm::mat4& GetViewMatrix() const
			{ return cameraViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const
			{ return cameraViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
		glm::mat4 cameraProjectionMatrix;
		glm::mat4 cameraViewMatrix;
		glm::mat4 cameraViewProjectionMatrix;
		glm::vec3 cameraPosition = { 0, 0, 0 };
		float cameraRotation = 0.0f;
	};
}