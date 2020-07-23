// Application Source file is used to start up the window, push layers, and other things
#include "Xpch.h"
#include <stdio.h>
#include "XEngine/Core/Application.h"
#include "XEngine/InputSystem/Input.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/InputSystem/XEngineInputCodes.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/OperatingSystems/Windows10/Win10Input.cpp"
#include <GLFW/glfw3.h>
namespace XEngine
{
	Application* Application::applicationInstance = nullptr;
	Application::Application()
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!applicationInstance, "Application already exists!");
		applicationInstance = this;
		applicationWindow = Window::Create();
		applicationWindow->SetEventCallback(X_BIND_EVENT_FN(Application::OnEvent));
		Renderer::Init();
		applicationImGuiLayer = new ImGuiLayer();
		PushOverlay(applicationImGuiLayer);
	}
	Application::~Application()
	{
		XPROFILE_FUNCTION();
		XCORE_INFO("Application Shutting Down");
		Renderer::Shutdown();
	}
	void Application::PushLayer(Layer* layer)
	{
		XPROFILE_FUNCTION();
		applicationLayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		XPROFILE_FUNCTION();
		applicationLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e)
	{
		XPROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(X_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(X_BIND_EVENT_FN(Application::OnWindowResize));
		for (auto it = applicationLayerStack.rbegin(); it != applicationLayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}
	void Application::Run() 
	{
		XPROFILE_FUNCTION();
		while (appRunning)
		{
			// Timestep
			XPROFILE_SCOPE("Run Loop");
			float time = (float)glfwGetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;
			// Update Layers
			if (!applicationMinimized)
			{
				{
					XPROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : applicationLayerStack)
						layer->OnUpdate(timestep);
				}	
				applicationImGuiLayer->Begin();
				{
					XPROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : applicationLayerStack)
						layer->OnImGuiRender();
				}
				applicationImGuiLayer->End();
			}
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
		XPROFILE_FUNCTION();
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