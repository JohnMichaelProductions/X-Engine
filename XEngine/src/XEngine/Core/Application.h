// Header file for the Application Class
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/Core/Window.h"
#include "XEngine/EventSystem/Event.h"
#include "XEngine/ImGuiLayer/ImGuiLayer.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/Buffer.h"
#include "XEngine/GraphicsSystem/Camera.h"
#include "XEngine/LayerSystem/LayerStack.h"
#include "XEngine/GraphicsSystem/VertexArray.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
int main(int argc, char** argv);
namespace XEngine
{
	class Application
	{
	public:
		// Defined in Source File
		Application();
		virtual ~Application();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		// Prototype in Header File
		Window& GetWindow()
			{ return *applicationWindow; }
		static Application& Get()
			{ return *applicationInstance; }
		void Close();
	private:
		// Defined in Source File
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		friend int ::main(int argc, char** argv);
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