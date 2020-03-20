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
namespace XEngine
{
	// Macro
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::instance = nullptr;
	// Constructor
	Application::Application() 
	{  
		XCORE_ASSERT(!instance, "Application already exists");
		instance = this;
		mainWindow = std::unique_ptr<Window>(Window::Create()); 
		mainWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		mainImGuiLayer = new ImGuiLayer;
		PushOverlay(mainImGuiLayer);
		// ---RENDERERING---
		glGenVertexArrays(1, &mainVertexArray);
		glBindVertexArray(mainVertexArray);
		glGenBuffers(1, &mainVertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, mainVertexBuffer);
		// Render Data
		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		VertexBuffer buffer = VertexBuffer::Create(sizeof(vertices), vertices);
		buffer.Bind();
		// Upload Data
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glGenBuffers(1, &mainIndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mainIndexBuffer);
		unsigned int indices[3] =
		{
			0,
			1,
			2
		};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// -----------------
		std::string vertexSourceCode = 
		R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";
		std::string fragmentSourceCode = 
		R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main() { color = vec4(v_Position * 0.5 + 0.5, 1.0); }
		)";
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
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
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