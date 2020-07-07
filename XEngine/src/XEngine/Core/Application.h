// Header file for the Application Class
#pragma once
#include "XCore.h"
#include "Window.h"
#include "Time.h"
#include "../EventSystem/Event.h"
#include "../EventSystem/ApplicationEvent.h"
#include "../ImGuiLayer/ImGuiLayer.h"
#include "../LayerSystem/LayerStack.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/Buffer.h"
#include "XEngine/Renderer/VertexArray.h"
#include "../Renderer/Camera.h"
namespace XEngine
{
	class XENGINE_API Application
	{
	public:
		// Defined in Source File
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		// Prototype in Header File
		inline Window& GetWindow()
			{ return *applicationWindow; }
		inline static Application& Get()
			{ return *applicationInstance; }
	private:
		// Defined in Source File
		bool OnWindowClose(WindowCloseEvent& e);
		bool appRunning = true;
		static Application* applicationInstance;
		std::unique_ptr<XEngine::Window> applicationWindow;
		LayerStack applicationLayerStack;
		ImGuiLayer* applicationImGuiLayer;
		float lastFrameTime = 0.0f;
	};
	Application* CreateApplication();
}