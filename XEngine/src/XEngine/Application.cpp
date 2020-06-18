#include <stdio.h>
#include "Xpch.h"
#include "Application.h"
#include "InputSystem/Input.h"
#include "LogSystem/Log.h"
#include "Renderer/Shader.h"
#include "Renderer/RendererAPI/Renderer.h"
namespace XEngine
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::instance = nullptr;
	Application::Application() 
	{  
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!instance, "Application already exists");
		instance = this;
		memberWindow = std::unique_ptr<Window>(Window::Create());	// Creating new window
		memberWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		memberImGuiLayer = new ImGuiLayer;
		PushOverlay(memberImGuiLayer);
		memberVertexArray.reset(VertexArray::Create());
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		memberVertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		memberVertexArray->SetIndexBuffer(indexBuffer);
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
		memberSquareVA->AddVertexBuffer(vertexBuffer);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		memberSquareVA->SetIndexBuffer(squareIB);
		std::string vertexSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader.shader");
		std::string fragmentSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader.shader");
		memberShader.reset(new Shader(vertexSourceCode, fragmentSourceCode));
		std::string vertexSourceCode2 = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader2.shader");
		std::string fragmentSourceCode2 = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader2.shader");
		memberShader2.reset(new Shader(vertexSourceCode2, fragmentSourceCode2));
	}
	Application::~Application() 
		{ XCORE_INFO("Application Shutting Down"); }
	void Application::PushLayer(Layer* layer) 
	{ 
		memberLayerStack.PushLayer(layer); 
		layer->OnAttach();
		XCORE_INFO(layer->GetName() + " has been pushed");
	}
	void Application::PushOverlay(Layer* layer) 
	{ 
		memberLayerStack.PushOverlay(layer); 
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e)

	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		XCORE_TRACE("{0}", e);
		for (auto it = memberLayerStack.end(); it != memberLayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}
	void Application::Run() 
	{
		while (appRunning)
		{
			RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
			RenderCommand::Clear();
			Renderer::BeginScene();
			memberShader2->Bind();
			Renderer::Submit(memberSquareVA);
			memberShader->Bind();
			Renderer::Submit(memberVertexArray);
			Renderer::EndScene();
			for (Layer* layer : memberLayerStack)
				layer->OnUpdate();
			memberImGuiLayer->Begin();
			for (Layer* layer : memberLayerStack)
				layer->OnImGuiRender();
			memberImGuiLayer->End();
			memberWindow->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		appRunning = false;
		return true;
	}
}