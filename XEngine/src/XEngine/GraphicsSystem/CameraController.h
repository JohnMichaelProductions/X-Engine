// Controller for camera to move and zoom in and out
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/GraphicsSystem/Camera.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
namespace XEngine
{
	struct OrthographicCameraBounds
	{
		float Left, Right, Bottom, Top;
		float GetWidth()
			{ return Right - Left; }
		float GetHeight()
			{ return Top - Bottom; }
	};
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);
		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);
		OrthographicCamera& GetCamera()
			{ return orthoCamera; }
		const OrthographicCamera& GetCamera() const
			{ return orthoCamera; }
		const OrthographicCameraBounds& GetBounds() const
			{ return cameraBounds; }
		float GetZoomLevel()
			{ return cameraZoomLevel; }
		void SetZoomLevel(float level)
			{ cameraZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		float cameraAspectRatio;
		float cameraZoomLevel = 1.0f;
		OrthographicCameraBounds cameraBounds;
		OrthographicCamera orthoCamera;
		bool rotationOn;
		glm::vec3 cameraPosition = {0,0,0};
		float cameraRotation = 0.0f;
		float cameraSpeed = 1.0f, rotationSpeed = 1.0f;
	};
}