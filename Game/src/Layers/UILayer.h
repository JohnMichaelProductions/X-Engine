/*#pragma once
#include "XEngine.h"
#include <glm/gtc/type_ptr.hpp>
class UILayer : public XEngine::Layer
{
public:
	UILayer(): Layer("UI")
	{
		UIVertexArray->XEngine::VertexArray::Create();
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		XEngine::Ref<XEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(XEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		XEngine::BufferLayout layout =
		{
			{ XEngine::ShaderDataType::Float3, "a_Position" },
			{ XEngine::ShaderDataType::Float4, "a_Color" }
		}; 
		vertexBuffer->SetLayout(layout);
		UIVertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		XEngine::Ref<XEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(XEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		UIVertexArray->SetIndexBuffer(indexBuffer);
		auto defaultShader = UIShaderLibrary.Load("Assets/Shaders/Default.glsl");
	}
	void OnUpdate(XEngine::Timestep timestep) override
	{
		// Background and clear
		XEngine::RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
		XEngine::RenderCommand::Clear();
		//XEngine::Renderer::BeginScene();
		auto defaultShader = UIShaderLibrary.Get("Default");
		defaultShader->Bind();
		XEngine::Renderer::Submit(UIVertexArray, defaultShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		XEngine::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override {}
	void OnEvent(XEngine::Event& event) override {}
private:
	XEngine::ShaderLibrary UIShaderLibrary;
	XEngine::Ref<XEngine::VertexArray> UIVertexArray;
	XEngine::Ref<XEngine::Shader> UIShader;
	glm::vec3 color = { 0.2,.3,.8f };
};*/