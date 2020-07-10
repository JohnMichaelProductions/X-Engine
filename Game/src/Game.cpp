// Where the game source code is written, stored, and called
#include <XEngine.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../vendor/ImGui/imgui.h"
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer"), applicationCamera(-1.6f, 1.6f, -.9f, .9f), applicationCameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		// Rendering
		// Triangle
		/*
		applicationVertexArray.reset(XEngine::VertexArray::Create());
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
		applicationVertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		XEngine::Ref<XEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(XEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		applicationVertexArray->SetIndexBuffer(indexBuffer);
		std::string vertexSourceCode = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/DefaultVertexShader.shader");
		std::string fragmentSourceCode = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/DefaultVertexShader.shader");
		applicationShader.reset(XEngine::Shader::Create(vertexSourceCode, fragmentSourceCode));
		*/
		// Square
		squareVertexArray.reset(XEngine::VertexArray::Create());
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
		std::string vertexSourceCode = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/SquareVertexShader.shader");
		std::string fragmentSourceCode = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/SquareFragmentShader.shader");
		squareShader.reset(XEngine::Shader::Create(vertexSourceCode, fragmentSourceCode));
		std::string textureVertexSource = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/TextureVertexShader.shader");
		std::string textureFragmentSource = XEngine::Shader::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/res/Shaders/TextureFragmentShader.shader");
		textureShader.reset(XEngine::Shader::Create(textureVertexSource, textureFragmentSource));
		texture = XEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<XEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}
	void OnUpdate(XEngine::Timestep timestep) override
	{
		// Background and clear
		XEngine::RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
		XEngine::RenderCommand::Clear();
		// Camera Movement
		if (XEngine::Input::IsKeyPressed(X_KEY_W))
			applicationCameraPosition.y += 1 * timestep;
		else if (XEngine::Input::IsKeyPressed(X_KEY_S))
			applicationCameraPosition.y -= 1 * timestep;
		if (XEngine::Input::IsKeyPressed(X_KEY_D))
			applicationCameraPosition.x += 1 * timestep;
		else if (XEngine::Input::IsKeyPressed(X_KEY_A))
			applicationCameraPosition.x -= 1 * timestep;
		applicationCamera.SetPosition(applicationCameraPosition);
		// Draw command
		XEngine::Renderer::BeginScene(applicationCamera);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(.1f));
		glm::vec4 redColor(.8f, .2f, .3f, 1.0f);
		glm::vec4 blueColor(.2f, .3f, .8f, 1.0f);
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
		texture->Bind();
		XEngine::Renderer::Submit(squareVertexArray, textureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		XEngine::Renderer::EndScene();
	}
	virtual void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", glm::value_ptr(color));
		ImGui::End();
	}
	void OnEvent(XEngine::Event& event) override {}
private:
	// Vertex Arrays
	XEngine::Ref<XEngine::VertexArray> applicationVertexArray;
	XEngine::Ref<XEngine::VertexArray> squareVertexArray;
	// Shaders
	XEngine::Ref<XEngine::Shader> applicationShader;
	XEngine::Ref<XEngine::Shader> squareShader;
	XEngine::Ref<XEngine::Shader> textureShader;
	XEngine::Ref<XEngine::Texture2D> texture;
	XEngine::OrthographicCamera applicationCamera;
	glm::vec3 applicationCameraPosition;
	glm::vec3 color = { 0.2,.3,.8f };
};
class Game : public XEngine::Application
{
public:
	Game()
	{ 
		XCORE_INFO("Game starting"); 
		PushLayer(new XLayer());
	}
	~Game()
		{ XCORE_INFO("Game shutting down!"); }
};
XEngine::Application* XEngine::CreateApplication()
	{ return new Game(); }