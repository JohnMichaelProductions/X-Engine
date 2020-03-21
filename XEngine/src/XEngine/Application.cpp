// C++ Libraries
#include <stdio.h>
// Top Files
#include "Xpch.h"
// Mid Files
#include "Application.h"
// Input System Files
#include "InputSystem/Input.h"
// Log System Files
#include "LogSystem/Log.h"
// GLAD Library
#include <GLAD/glad.h>

#include "Renderer/Shader.h"
namespace XEngine
{
	// Macro
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::instance = nullptr;
	// Constructor
	Application::Application() 
	{  
		XCORE_INFO("Application(Class) has been created");
		XCORE_ASSERT(!instance, "Application already exists");
		instance = this;
		mainWindow = std::unique_ptr<Window>(Window::Create()); 
		mainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		mainImGuiLayer = new ImGuiLayer;
		PushOverlay(mainImGuiLayer);
		// ---RENDERERING---
		glGenVertexArrays(1, &mainVertexArray);
		glBindVertexArray(mainVertexArray);
		// Render Data
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		mainVertex.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		// Upload Data
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		uint32_t indices[3] = { 0, 1, 2 };
		mainIndex.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// -----------------
		std::string vertexSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader.shader");
		std::string fragmentSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader.shader");
		mainShader.reset(new Shader(vertexSourceCode, fragmentSourceCode));
	}
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	// Push Layer Function
	void Application::PushLayer(Layer* layer) 
	{ 
		mainLayerStack.PushLayer(layer); 
		layer->OnAttach();
	}
	// Push Overlay Function
	void Application::PushOverlay(Layer* layer) 
	{ 
		mainLayerStack.PushOverlay(layer); 
		layer->OnAttach();
	}
	// On Event Function
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		XCORE_TRACE("{0}", e);
		for (auto it = mainLayerStack.end(); it != mainLayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	// Run Function: Keeps application alive and running
	void Application::Run() 
	{
		// Keeps the application running
		while (mainRunning)
		{
			glClearColor(.1743f, .2988f, .5270f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			mainShader->Bind();
			glBindVertexArray(mainVertexArray);
			glDrawElements(GL_TRIANGLES, mainIndex->GetCount(), GL_UNSIGNED_INT, nullptr);
			for (Layer* layer : mainLayerStack)
				layer->OnUpdate();
			mainImGuiLayer->Begin();
			for (Layer* layer : mainLayerStack)
				layer->OnImGuiRender();
			mainImGuiLayer->End();
			// Update every frame
			mainWindow->OnUpdate(); 
		}
	}
	// On Window Close Function: Called when application is closed causing the application to stop running
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		mainRunning = false;
		return true;
	}
}