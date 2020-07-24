// Source file for Renderer2D Includes startup and shutdown as well as draw calls
#include "Xpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/VertexArray.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer2D.h"
#include "XEngine/GraphicsSystem/Renderer/RenderCommand.h"
namespace XEngine
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		// TODO: texid
	};
	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};
	static Renderer2DData rendererData;
	void Renderer2D::Init()
	{
		XPROFILE_FUNCTION();
		rendererData.VertexArray = VertexArray::Create();
		rendererData.VertexBuffer = VertexBuffer::Create(rendererData.MaxVertices * sizeof(QuadVertex));
		rendererData.VertexBuffer->SetLayout
		({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
			{ShaderDataType::Float2, "a_TexCoord"}
		});
		rendererData.VertexArray->AddVertexBuffer(rendererData.VertexBuffer);
		rendererData.QuadVertexBufferBase = new QuadVertex[rendererData.MaxVertices];
		uint32_t* quadIndices = new uint32_t[rendererData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < rendererData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;
			offset += 4;
		}
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, rendererData.MaxIndices);
		rendererData.VertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;
		// Textures
		rendererData.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		rendererData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
		rendererData.TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		rendererData.TextureShader->Bind();
		rendererData.TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown() {}
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		XPROFILE_FUNCTION();
		rendererData.TextureShader->Bind();
		rendererData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		rendererData.QuadIndexCount = 0;
		rendererData.QuadVertexBufferPtr = rendererData.QuadVertexBufferBase;
	}
	void Renderer2D::EndScene()
	{
		XPROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)rendererData.QuadVertexBufferPtr - (uint8_t*)rendererData.QuadVertexBufferBase;		rendererData.VertexBuffer->SetData(rendererData.QuadVertexBufferBase, dataSize);
		Flush();
	}
	void Renderer2D::Flush()
		{ RenderCommand::DrawIndexed(rendererData.VertexArray, rendererData.QuadIndexCount); }
	// Draw Calls
	// Draw Quad (x, y) (Color)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{ DrawQuad({position.x, position.y, 0.0}, size, color); }
	// Draw Quad (x, y, z) (Color)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		rendererData.QuadVertexBufferPtr->Position = position;
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadIndexCount += 6;
		/*rendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		rendererData.WhiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData.TextureShader->SetMat4("u_Transform", transform);
		rendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData.VertexArray);*/
	}
	// Draw Quad (x, y) (Texture)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
		{ DrawQuad({position.x, position.y, 0.0}, size, texture, tilingFactor, tintColor); }
	// Draw Quad (x, y, z) (Texture)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		rendererData.TextureShader->SetFloat4("u_Color", tintColor);
		rendererData.TextureShader->SetFloat("m_TilingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData.TextureShader->SetMat4("u_Transform", transform);
		rendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData.VertexArray);
	}
	// Draw Rotated Quad (x, y) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{ DrawRotatedQuad({position.x, position.y, 0.0}, size, rotation, color); }
	// Draw Rotated Quad (x, y, z) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		rendererData.TextureShader->SetFloat4("u_Color", color);
		rendererData.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		rendererData.WhiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData.TextureShader->SetMat4("u_Transform", transform);
		rendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData.VertexArray);
	}
	// Draw Rotated Quad (x, y) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
		{ DrawRotatedQuad({ position.x, position.y, 0.0 }, size, rotation, texture, tilingFactor, tintColor); }
	// Draw Rotated Quad (x, y, z) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		rendererData.TextureShader->SetFloat4("u_Color", tintColor);
		rendererData.TextureShader->SetFloat("m_TilingFactor", tilingFactor);
		texture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		rendererData.TextureShader->SetMat4("u_Transform", transform);
		rendererData.VertexArray->Bind();
		RenderCommand::DrawIndexed(rendererData.VertexArray);
	}
}