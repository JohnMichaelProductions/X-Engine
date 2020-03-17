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
		inline static Application& Get() { return *instance; }
		// -------------------------
	private:
		// ---VARIABLES---
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> mainWindow;
		ImGuiLayer* mainImGuiLayer;
		bool mainRunning = true;
		LayerStack mainLayerStack;
		unsigned int mainVertexArray, mainVertexBuffer, mainIndexBuffer;
		static Application* instance;
		// ---------------
	};
	Application* CreateApplication();
}

