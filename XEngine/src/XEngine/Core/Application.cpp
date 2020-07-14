// Application Source file is used to start up the window, push layers, and other things
#include <stdio.h>
#include "Xpch.h"
#include "Application.h"
#include "XEngine/LogSystem/Log.h"
#include "XEngine/InputSystem/Input.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/InputSystem/XEngineInputCodes.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/OperatingSystems/Windows10/Win10Input.cpp"
#include <GLFW/glfw3.h>
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::applicationInstance = nullptr;
	Application::Application()
	{
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!applicationInstance, "Application already exists!");
		applicationInstance = this;
		applicationWindow = std::unique_ptr<Window>(Window::Create());
		applicationWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		Renderer::Init();
		applicationImGuiLayer = new ImGuiLayer();
		PushOverlay(applicationImGuiLayer);
	}
	Application::~Application() 
		{ XCORE_INFO("Application Shutting Down"); }
	void Application::PushLayer(Layer* layer) 
	{ 
		applicationLayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) 
	{ 
		applicationLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		for (auto it = applicationLayerStack.end(); it != applicationLayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}
	void Application::Run() 
	{
		while (appRunning)
		{
			// Timestep
			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;
			// Update Layers
			if (!applicationMinimized)
				for (Layer* layer : applicationLayerStack)
					layer->OnUpdate(timestep);
			applicationImGuiLayer->Begin();
			for (Layer* layer : applicationLayerStack)
				layer->OnImGuiRender();
			applicationImGuiLayer->End();
			applicationWindow->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		appRunning = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			applicationMinimized = true;
			return false;
		}
		applicationMinimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}