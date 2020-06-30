// Where the game source code is written, stored, and called
#include <XEngine.h>
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("Name"), applicationCamera(-1.6f, 1.6f, -.9f, .9f), applicationCameraPosition({ 0.0f, 0.0f, 0.0f })
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
	void OnUpdate() override
	{
		// Background and clear
		XEngine::RenderCommand::SetClearColor({ .2f, .2f, .2f, 1 });
		XEngine::RenderCommand::Clear();
		if (XEngine::Input::IsKeyPressed(X_KEY_W))
			applicationCameraPosition.y += 0.01;
		else if (XEngine::Input::IsKeyPressed(X_KEY_S))
			applicationCameraPosition.y -= 0.01;
		if (XEngine::Input::IsKeyPressed(X_KEY_D))
			applicationCameraPosition.x += 0.01;
		else if (XEngine::Input::IsKeyPressed(X_KEY_A))
			applicationCameraPosition.x -= 0.01;
		applicationCamera.SetPosition(applicationCameraPosition);
		// Draw command
		XEngine::Renderer::BeginScene(applicationCamera);
		XEngine::Renderer::Submit(applicationVertexArray, applicationShader);
		XEngine::Renderer::EndScene();
	}
	void OnImGuiRender() override
	{

	}
	void OnEvent(XEngine::Event& event) override
	{

	}
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