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
	public:												// {PUBLIC}
		Application();									// Constructor Function: Called opon creation, Check Source Files
		virtual ~Application();							// (Virtual) Destructor Function: Called when object is deleted, Check Source Files
		void Run();										// Run Function: Check Source Files
		void OnEvent(Event& e);							// On Event Function: Check Source Files
		void PushLayer(Layer* layer);					// Push Layer Function: Check Source Files
		void PushOverlay(Layer* layer);					// Push Overlay Function: Check Source File
		inline Window& GetWindow()						// (Inline) Get Window Function: Returns Window
			{ return *memberWindow; }	
		inline static Application& Get()				// (Inline) (Static) Get Function: Returns the application
			{ return *instance; }	
	private:											// {PRIVATE}
		bool OnWindowClose(WindowCloseEvent& e);		// On Window Close Function: Check Source File
		bool appRunning = true;							// Boolean Variable: Boolean for telling whether the application is running
		static Application* instance;					// (Static) Application Variable: The application
		LayerStack memberLayerStack;					// Layer Stack Variable: Layer Stack for layer system
		ImGuiLayer* memberImGuiLayer;					// ImGui Layer Variable: ImGui layer for application
		std::unique_ptr<Window> memberWindow;			// Window Variable: Window for application
		std::shared_ptr<VertexArray> memberVertexArray;
		std::shared_ptr<Shader> memberShader;			// Shader Variable: Shader for renderers
		std::shared_ptr<Shader> memberShader2;			// Shader Variable: Shader for renderers
		std::shared_ptr<VertexArray> memberSquareVA;
	};
	Application* CreateApplication();					// Create Application Function: Creates Application
}

