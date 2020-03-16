// C++ Libraries
#include <stdio.h>
// Top Files
#include "Xpch.h"
// Mid Files
#include "Application.h"
// Input System Files
#include "InputSystem/Input.h"
// Log System Files
#include "LogSystem/Log.h"
// GLAD Library
#include <GLAD/glad.h>
namespace XEngine
{
	// Macro
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	// Constructor: Print Application Created
	Application::Application() 
	{  
		XCORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		mainWindow = std::unique_ptr<Window>(Window::Create()); 
		mainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	// Push Layer Function
	void Application::PushLayer(Layer* layer) 
	{ 
		m_LayerStack.PushLayer(layer); 
		layer->OnAttach();
	}
	// Push Overlay Function
	void Application::PushOverlay(Layer* layer) 
	{ 
		m_LayerStack.PushOverlay(layer); 
		layer->OnAttach();
	}
	// On Event Function
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		XCORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	// Run Function: Keeps application alive and running
	void Application::Run() 
	{
		// Keeps the application running
		while (m_Running)
		{
			glClearColor(.1743f, .2988f, .5270f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			// Update every frame
			mainWindow->OnUpdate(); 
		}
	}
	// On Window Close Function: Called when application is closed causing the application to stop running
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}