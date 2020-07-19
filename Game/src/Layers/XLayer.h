#pragma once
#include "XEngine.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include "../vendor/ImGui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer"), applicationCamera(1920.0f / 1080.0f, true)
	{
		squareVertexArray = XEngine::VertexArray::Create();
		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		std::shared_ptr<XEngine::VertexBuffer> squareVB;
		squareVB.reset(XEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout
		({
			{ XEngine::ShaderDataType::Float3, "a_Position" },
			{ XEngine::ShaderDataType::Float2, "a_TexCoord" }
		});
		squareVertexArray->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<XEngine::IndexBuffer> squareIB;
		squareIB.reset(XEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVertexArray->SetIndexBuffer(squareIB);
		auto textureShader = applicationShaderLibrary.Load("Assets/Shaders/Texture.glsl");
		texture = XEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
		logoTexture = XEngine::Texture2D::Create("Assets/Textures/ChernoLogo.png");
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(XEngine::Timestep timestep) override
	{
		applicationCamera.OnUpdate(timestep);
		// Background and clear
		XEngine::RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
		XEngine::RenderCommand::Clear();
		// Draw command
		XEngine::Renderer::BeginScene(applicationCamera.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(.1f));
		glm::vec4 redColor(.8f, .2f, .3f, 1.0f);
		glm::vec4 blueColor(.2f, .3f, .8f, 1.0f);
		auto squareShader = XEngine::Shader::Create("Assets/Shaders/FlatColor.glsl");
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(squareShader)->Bind();
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(squareShader)->UploadUniformFloat3("u_Color", color);
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 15; x++)
			{
				glm::vec3 pos(x * .11f, y * .11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				XEngine::Renderer::Submit(squareVertexArray, squareShader, transform);
			}
		}
		auto textureShader = applicationShaderLibrary.Get("Texture");
		texture->Bind();
		XEngine::Renderer::Submit(squareVertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		logoTexture->Bind();
		XEngine::Renderer::Submit(squareVertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		XEngine::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(color));
		ImGui::End();
	}
	void OnEvent(XEngine::Event& e) override
		{ applicationCamera.OnEvent(e); }
private:
	XEngine::ShaderLibrary applicationShaderLibrary;
	XEngine::Ref<XEngine::VertexArray> squareVertexArray;
	XEngine::Ref<XEngine::Texture2D> texture, logoTexture;
	XEngine::OrthographicCameraController applicationCamera;
	glm::vec3 color = { 0.2f,.3f,.8f };
};