// Where the game source code is written, stored, and called
#include <XEngine.h>
#include <glm/gtc/matrix_transform.hpp>
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer"), applicationCamera(-1.6f, 1.6f, -.9f, .9f), applicationCameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		// Rendering
		applicationVertexArray.reset(XEngine::VertexArray::Create());
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};
		std::shared_ptr<XEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(XEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		XEngine::BufferLayout layout =
		{
			{ XEngine::ShaderDataType::Float3, "a_Position" },
			{ XEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		applicationVertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<XEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(XEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		applicationVertexArray->SetIndexBuffer(indexBuffer);
		std::string vertexSourceCode = XEngine::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/Resources/DefaultVertexShader.shader");
		std::string fragmentSourceCode = XEngine::ConvertShader("C:/JohnMichaelProductions/X-Engine/XEngine/src/Resources/DefaultFragmentShader.shader");
		applicationShader.reset(new XEngine::Shader(vertexSourceCode, fragmentSourceCode));
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
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		

		glm::vec4 redColor(.8f, .2f, .3f, 1.0f);
		glm::vec4 blueColor(.2f, .3f, .8f, 1.0f);


		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 50; x++)
			{
				glm::vec3 pos(x * 1.0f, y * 1.0f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == 0)
					applicationVertexArray->UploadUniformFloat4("u_Color", redColor);
				else
					applicationVertexArray->UploadUniformFloat4("u_Color", blueColor);
				XEngine::Renderer::Submit(applicationVertexArray, applicationShader, transform);
			}
		}
		XEngine::Renderer::EndScene();
	}
	void OnImGuiRender() override {}
	void OnEvent(XEngine::Event& event) override {}
private:
	std::shared_ptr<XEngine::VertexArray> applicationVertexArray;
	std::shared_ptr<XEngine::Shader> applicationShader;
	XEngine::OrthographicCamera applicationCamera;
	glm::vec3 applicationCameraPosition;
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