// Header file for the Application Class
#pragma once
#include "Time.h"
#include "XCore.h"
#include "Window.h"
#include "XEngine/EventSystem/Event.h"
#include "XEngine/ImGuiLayer/ImGuiLayer.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/Buffer.h"
#include "XEngine/GraphicsSystem/Camera.h"
#include "XEngine/LayerSystem/LayerStack.h"
#include "XEngine/GraphicsSystem/VertexArray.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
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
		bool OnWindowResize(WindowResizeEvent& e);
		bool appRunning = true;
		bool applicationMinimized = false;
		static Application* applicationInstance;
		std::unique_ptr<XEngine::Window> applicationWindow;
		LayerStack applicationLayerStack;
		ImGuiLayer* applicationImGuiLayer;
		float lastFrameTime = 0.0f;
	};
	Application* CreateApplication();
}