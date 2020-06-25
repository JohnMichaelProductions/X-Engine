// Header file for the Application Class
#pragma once
#include "XCore.h"
#include "Window.h"
#include "EventSystem/Event.h"
#include "EventSystem/ApplicationEvent.h"
#include "ImGuiLayer/ImGuiLayer.h"
#include "LayerSystem/LayerStack.h"
#include "XEngine/Renderer/Shader.h"
#include "XEngine/Renderer/Buffer.h"
#include "XEngine/Renderer/VertexArray.h"
namespace XEngine
{
	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow()
			{ return *applicationWindow; }
		inline static Application& Get()
			{ return *applicationInstance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool appRunning = true;
		static Application* applicationInstance;
		LayerStack applicationLayerStack;
		ImGuiLayer* applicationImGuiLayer;
		std::unique_ptr<Window> applicationWindow;
		std::shared_ptr<VertexArray> applicationVertexArray;
		std::shared_ptr<Shader> applicationShader;
	};
	Application* CreateApplication();
}