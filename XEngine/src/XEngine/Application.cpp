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
	static GLenum ShaderDataTypeConvertToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case XEngine::ShaderDataType::Float:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float2:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float3:	return GL_FLOAT;
			case XEngine::ShaderDataType::Float4:	return GL_FLOAT;
			case XEngine::ShaderDataType::Mat3:		return GL_FLOAT;
			case XEngine::ShaderDataType::Mat4:		return GL_FLOAT;
			case XEngine::ShaderDataType::Int:		return GL_INT;
			case XEngine::ShaderDataType::Int2:		return GL_INT;
			case XEngine::ShaderDataType::Int3:		return GL_INT;
			case XEngine::ShaderDataType::Int4:		return GL_INT;
			case XEngine::ShaderDataType::Bool:		return GL_BOOL;
		}
		XCORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
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
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		mainVertex.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout =
			{
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" }
			};
			mainVertex->SetLayout(layout);
		}
		uint32_t index = 0;
		const auto& layout = mainVertex->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeConvertToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, mainVertex->GetLayout().GetStride(), (const void *)element.Offset);
			index++;
		}
		// Upload Data
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
	void Application::OnEvent(Event& e) // On Event Function

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