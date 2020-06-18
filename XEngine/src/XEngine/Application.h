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
			{ return *memberWindow; }
		inline static Application& Get()
			{ return *instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool appRunning = true;
		static Application* instance;
		LayerStack memberLayerStack;
		ImGuiLayer* memberImGuiLayer;
		std::unique_ptr<Window> memberWindow;
		std::shared_ptr<VertexArray> memberVertexArray;
		std::shared_ptr<Shader> memberShader;
		std::shared_ptr<Shader> memberShader2;
		std::shared_ptr<VertexArray> memberSquareVA;
	};
	Application* CreateApplication();
}

