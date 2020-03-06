#pragma once
#include "XCore.h"
#include "Window.h"
#include "XEngine/LayerStack.h"
#include "EventSystem/Event.h"
#include "../XEngine/EventSystem/ApplicationEvent.h"
namespace XEngine
{
	class XENGINE_API Application
	{
	public:
		// Creates functions
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	Application* CreateApplication();
}

