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
	Application* Application::applicationInstance = nullptr;
	Application::Application()
	{  
		XCORE_INFO("Application starting");
		XCORE_ASSERT(!applicationInstance, "Application already exists!");
		applicationInstance = this;
		applicationWindow = std::unique_ptr<Window>(Window::Create());
		applicationWindow->SetEventCallback(BIND_EVENT_FN(OnEvent));
		applicationImGuiLayer = new ImGuiLayer();
		PushOverlay(applicationImGuiLayer);
		applicationVertexArray.reset(VertexArray::Create());
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
		applicationVertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		applicationVertexArray->SetIndexBuffer(indexBuffer);
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
		applicationShader.reset(new Shader(vertexSrc, fragmentSrc));
		//std::string vertexSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultVertexShader.shader");
		//std::string fragmentSourceCode = ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/DefaultFragmentShader.shader");
	}
	Application::~Application() 
		{ XCORE_INFO("Application Shutting Down"); }
	void Application::PushLayer(Layer* layer) 
	{ 
		applicationLayerStack.PushLayer(layer);
		layer->OnAttach();
		XCORE_INFO(layer->GetName() + " has been pushed");
	}
	void Application::PushOverlay(Layer* layer) 
	{ 
		applicationLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		XCORE_TRACE("{0}", e);
		for (auto it = applicationLayerStack.end(); it != applicationLayerStack.begin(); )
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
			// Background and clear
			RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
			RenderCommand::Clear();
			// Draw command
			Renderer::BeginScene();
			applicationShader->Bind();
			Renderer::Submit(applicationVertexArray);
			Renderer::EndScene();
			// Update Layers
			for (Layer* layer : applicationLayerStack)
				layer->OnUpdate();
			applicationImGuiLayer->Begin();
			for (Layer* layer : applicationLayerStack)
				layer->OnImGuiRender();
			applicationImGuiLayer->End();
			applicationWindow->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		appRunning = false;
		return true;
	}
}
