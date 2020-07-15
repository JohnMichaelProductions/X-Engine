#include "Xpch.h"
#include "XEngine/GraphicsSystem/CameraController.h"
#include "XEngine/InputSystem/Input.h"
#include "XEngine/InputSystem/XEngineInputCodes.h"
namespace XEngine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) : cameraAspectRatio(aspectRatio), rotationOn(rotation), orthoCamera(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio* cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel){}
	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		if (Input::IsKeyPressed(X_KEY_W))
		{
			cameraPosition.x += -sin(glm::radians(cameraRotation)) * cameraSpeed * timestep;
			cameraPosition.y += cos(glm::radians(cameraRotation)) * cameraSpeed * timestep;
		}
		else if (Input::IsKeyPressed(X_KEY_S))
		{
			cameraPosition.x -= -sin(glm::radians(cameraRotation)) * cameraSpeed * timestep;
			cameraPosition.y -= cos(glm::radians(cameraRotation)) * cameraSpeed * timestep;
		}
		if (Input::IsKeyPressed(X_KEY_D))
		{
			cameraPosition.x += cos(glm::radians(cameraRotation)) * cameraSpeed * timestep;
			cameraPosition.y += sin(glm::radians(cameraRotation)) * cameraSpeed * timestep;
		}
		else if (Input::IsKeyPressed(X_KEY_A))
		{
			cameraPosition.x -= cos(glm::radians(cameraRotation)) * cameraSpeed * timestep;
			cameraPosition.y -= sin(glm::radians(cameraRotation)) * cameraSpeed * timestep;
		}		orthoCamera.SetPosition(cameraPosition);
		if (rotationOn)
		{
			if (Input::IsKeyPressed(X_KEY_E))
				cameraRotation += rotationSpeed * timestep;
			else if (Input::IsKeyPressed(X_KEY_Q))
				cameraRotation -= rotationSpeed * timestep;
			if (cameraRotation > 180.0f)
				cameraRotation -= 360.0f;
			else if (cameraRotation <= -180.0f)
				cameraRotation += 360.0f;
			orthoCamera.SetRotation(cameraRotation);
		}
		cameraSpeed = cameraZoomLevel;
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispacter(e);
		dispacter.Dispatch<MouseScrolledEvent>(X_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispacter.Dispatch<WindowResizeEvent>(X_BIND_EVENT_FN(OrthographicCameraController::OnWindowResize));
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		cameraZoomLevel -= e.GetYOffset() * 0.25f;
		cameraZoomLevel = std::max(cameraZoomLevel, .25f);
		orthoCamera.SetProjectionMatrix(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);
		return false;
	}
	bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
	{
		cameraAspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		orthoCamera.SetProjectionMatrix(-cameraAspectRatio * cameraZoomLevel, cameraAspectRatio * cameraZoomLevel, -cameraZoomLevel, cameraZoomLevel);
		return false;
	}
}