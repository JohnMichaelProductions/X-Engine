#pragma once
// Mid Files
#include "XCore.h"
#include "Window.h"
// Event System Files
#include "EventSystem/Event.h"
#include "EventSystem/ApplicationEvent.h"
// ImGui Layer Files
#include "ImGuiLayer/ImGuiLayer.h"
// Layer System Files
#include "LayerSystem/LayerStack.h"
namespace XEngine
{
	class XENGINE_API Application
	{
	public:
		// ---FUNCTIONS---
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		// ---------------
		// ---FUNCTION PROTOTYPES---
		inline Window& GetWindow() { return *mainWindow; }
		inline static Application& Get() { return *s_Instance; }
		// -------------------------
	private:
		// ---VARIABLES---
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> mainWindow;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		// ---------------
	};
	Application* CreateApplication();
}

