#include "Xpch.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/VertexArray.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer2D.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
#include "XEngine/GraphicsSystem/Renderer/RenderCommand.h"
namespace XEngine
{
	struct Renderer2DData
	{
		Ref<VertexArray> vertexArray;
		Ref<Shader> colorShader;
	};
	static Renderer2DData* rendererData;
	void Renderer2D::Init()
	{
		rendererData = new Renderer2DData();
		rendererData->vertexArray = VertexArray::Create();
		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ {ShaderDataType::Float3, "a_Position"} });
		rendererData->vertexArray->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		rendererData->vertexArray->SetIndexBuffer(squareIB);
		rendererData->colorShader = Shader::Create("Assets/Shaders/Square.shader");
	}
	void Renderer2D::Shutdown()
		{ delete rendererData; }
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->colorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->colorShader)->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->colorShader)->UploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}
	void Renderer2D::EndScene() {}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{ DrawQuad({position.x, position.y, 0.0}, size, color); }
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->colorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(rendererData->colorShader)->UploadUniformFloat4("u_Color", color);
		rendererData->vertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData->vertexArray);
	}
}