#include <stdio.h>
#include "Xpch.h"
#include "Application.h"
#include "InputSystem/Input.h"
#include "LogSystem/Log.h"
#include <GLAD/glad.h>
#include "Renderer/Shader.h"
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)	// Bind Event Macro: Binds event
	Application* Application::instance = nullptr;
	Application::Application() 
	{  
		XCORE_INFO("Application(Class) has been created");
		XCORE_ASSERT(!instance, "Application already exists");
		instance = this;
		memberWindow = std::unique_ptr<Window>(Window::Create());
		memberWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		memberImGuiLayer = new ImGuiLayer;
		PushOverlay(memberImGuiLayer);
		// ---RENDERERING---
		glGenVertexArrays(1, &memberVertexArray);
		glBindVertexArray(memberVertexArray);
		float vertices[3 * 7] =								// Renderer Data
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		memberVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout =
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};
			memberVertexBuffer->SetLayout(layout);
		}
		uint32_t index = 0;
		const auto& layout = memberVertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeConvertToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, memberVertexBuffer->GetLayout().GetStride(), (const void *)element.Offset);
			index++;
		}
		// Upload Data
		uint32_t indices[3] = { 0, 1, 2 };
		memberIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// -----------------
		std::string vertexSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader.shader");
		std::string fragmentSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader.shader");
		memberShader.reset(new Shader(vertexSourceCode, fragmentSourceCode));
	}
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	// Push Layer Function
	void Application::PushLayer(Layer* layer) 
	{ 
		memberLayerStack.PushLayer(layer); 
		layer->OnAttach();
	}
	// Push Overlay Function
	void Application::PushOverlay(Layer* layer) 
	{ 
		memberLayerStack.PushOverlay(layer); 
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e) // On Event Function

	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		XCORE_TRACE("{0}", e);
		for (auto it = memberLayerStack.end(); it != memberLayerStack.begin(); )
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
		while (memberRunning)
		{
			glClearColor(.1743f, .2988f, .5270f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			memberShader->Bind();
			glBindVertexArray(memberVertexArray);
			glDrawElements(GL_TRIANGLES, memberIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			for (Layer* layer : memberLayerStack)
				layer->OnUpdate();
			memberImGuiLayer->Begin();
			for (Layer* layer : memberLayerStack)
				layer->OnImGuiRender();
			memberImGuiLayer->End();
			// Update every frame
			memberWindow->OnUpdate();
		}
	}
	// On Window Close Function: Called when application is closed causing the application to stop running
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		memberRunning = false;
		return true;
	}
}