#pragma region INCLUDE / NAMESPACES
#include "Xpch.h"
#include <stdio.h>
#include "Application.h"
#include "../XEngine/EventSystem/ApplicationEvent.h"
#include "../XEngine/Log.h"
#include <GLFW/glfw3.h>
#pragma endregion
namespace XEngine
{
	// Constructor: Print Application Created
	Application::Application() {  m_Window = std::unique_ptr<Window>(Window::Create()); }
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	// Function: Keeps application alive and running
	#pragma region RUN FUNCTION
	void Application::Run() 
	{
		// Keeps the application running
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate(); 
		}
	}
	#pragma endregion
}