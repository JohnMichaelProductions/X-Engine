// Application Source File
#include <stdio.h>
#include "Xpch.h"
#include "Application.h"
#include "InputSystem/Input.h"
#include "LogSystem/Log.h"
#include "Renderer/Shader.h"
#include "Renderer/RendererAPI/Renderer.h"
#include "Platforms/OperatingSystems/Windows10/Win10Input.cpp"
#include "InputSystem/XEngineInputCodes.h"
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::applicationInstance = nullptr;
	Application::Application()
	{
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!applicationInstance, "Application already exists!");
		applicationInstance = this;
		eventUpdates = false;
		applicationWindow = std::unique_ptr<Window>(Window::Create());
		applicationWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		applicationImGuiLayer = new ImGuiLayer();
		PushOverlay(applicationImGuiLayer);
	}
	Application::~Application() 
		{ XCORE_INFO("Application Shutting Down"); }
	void Application::PushLayer(Layer* layer) 
	{ 
		applicationLayerStack.PushLayer(layer);
		layer->OnAttach();
		XCORE_INFO(layer->GetName() + " has been pushed");
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
		if(eventUpdates)
			XCORE_TRACE("{0}", e);
		for (auto it = applicationLayerStack.end(); it != applicationLayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}
	void Application::Run() 
	{
		float x = 0.0f;
		float y = 0.0f;
		while (appRunning)
		{

			// Update Layers
			for (Layer* layer : applicationLayerStack)
				layer->OnUpdate();
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
}
