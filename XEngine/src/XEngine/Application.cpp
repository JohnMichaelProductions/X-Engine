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
		memberVertexArray.reset(VertexArray::Create());
		// ---RENDERERING---
		float vertices[3 * 7] =								// Renderer Data
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;

		memberVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		memberVertexBuffer->SetLayout(layout);
		memberVertexArray->AddVertexBuffer(memberVertexBuffer);
		// Upload Data
		uint32_t indices[3] = { 0, 1, 2 };
		memberIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		memberVertexArray->SetIndexBuffer(memberIndexBuffer);
		// -----------------
		memberSquareVA.reset(VertexArray::Create());
		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB; 
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ {ShaderDataType::Float3, "a_Position"} });
		memberSquareVA->AddVertexBuffer(memberVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		memberSquareVA->SetIndexBuffer(squareIB);
		// Shader Stuff
		std::string vertexSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader.shader");
		std::string fragmentSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader.shader");
		memberShader.reset(new Shader(vertexSourceCode, fragmentSourceCode));
		std::string vertexSourceCode2 = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader2.shader");
		std::string fragmentSourceCode2 = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader2.shader");
		memberShader2.reset(new Shader(vertexSourceCode2, fragmentSourceCode2));
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
			glClearColor(.2f, .2f, .2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			memberShader2->Bind();
			memberSquareVA->Bind();
			glDrawElements(GL_TRIANGLES, memberSquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);


			memberShader->Bind();
			memberVertexArray->Bind();
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