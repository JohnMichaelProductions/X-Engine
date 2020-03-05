#pragma region INCLUDE / NAMESPACES
#include "Xpch.h"
#include <stdio.h>
#include "Application.h"
#include "../XEngine/Log.h"
#include <GLFW/glfw3.h>
#pragma endregion
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	// Constructor: Print Application Created
	Application::Application() 
	{  
		m_Window = std::unique_ptr<Window>(Window::Create()); 
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		X_CORE_TRACE("{0}", e);
	}
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
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	#pragma endregion
}