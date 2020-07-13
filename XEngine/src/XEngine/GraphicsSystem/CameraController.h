// Controller for camera to move and zoom in and out
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/GraphicsSystem/Camera.h"
namespace XEngine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation);
		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera()
			{ return orthoCamera; }
		const OrthographicCamera& GetCamera() const
			{ return orthoCamera; }
		float cameraSpeed = 1.0f, rotationSpeed = 1.0f;
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		float cameraAspectRatio;
		float cameraZoomLevel = 1.0f;
		OrthographicCamera orthoCamera;
		bool rotationOn = false;
		glm::vec3 cameraPosition = {0,0,0};
		float cameraRotation = 0.0f;
	};
}