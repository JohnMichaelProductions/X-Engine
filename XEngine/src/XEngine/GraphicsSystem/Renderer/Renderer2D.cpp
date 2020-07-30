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
		float TexIndex;
		float TillingFactor;
	};
	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps
		Ref<VertexArray> VertexArray;
		Ref<VertexBuffer> VertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;
		glm::vec4 QuadVertexPositions[4];
	}; 
	static Renderer2DData rendererData;
	void Renderer2D::Init()
	{
		XPROFILE_FUNCTION();
		rendererData.VertexArray = VertexArray::Create();
		rendererData.VertexBuffer = VertexBuffer::Create(rendererData.MaxVertices * sizeof(QuadVertex));
		rendererData.VertexBuffer->SetLayout
		({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"},
			{ ShaderDataType::Float2, "a_TexCoord"},
			{ ShaderDataType::Float, "a_TexIndex"},
			{ ShaderDataType::Float, "a_TillingFactor"}
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
		int32_t samplers[rendererData.MaxTextureSlots];
		for (uint32_t i = 0; i < rendererData.MaxTextureSlots; i++)
			samplers[i] = i;
		rendererData.TextureShader = Shader::Create("Assets/Shaders/Texture.glsl");
		rendererData.TextureShader->Bind();
		rendererData.TextureShader->SetIntArray("u_Textures", samplers, rendererData.MaxTextureSlots);
		// Setting all texture slots to zero
		rendererData.TextureSlots[0] = rendererData.WhiteTexture;
		rendererData.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		rendererData.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		rendererData.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		rendererData.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
	}
	void Renderer2D::Shutdown() {}
	void Renderer2D::BeginScene(OrthographicCamera& camera)
	{
		XPROFILE_FUNCTION();
		rendererData.TextureShader->Bind();
		rendererData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		rendererData.QuadIndexCount = 0;
		rendererData.QuadVertexBufferPtr = rendererData.QuadVertexBufferBase;
		rendererData.TextureSlotIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		XPROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)rendererData.QuadVertexBufferPtr - (uint8_t*)rendererData.QuadVertexBufferBase;		rendererData.VertexBuffer->SetData(rendererData.QuadVertexBufferBase, dataSize);
		Flush();
	}
	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
			rendererData.TextureSlots[i]->Bind(i);
		RenderCommand::DrawIndexed(rendererData.VertexArray, rendererData.QuadIndexCount);
	}
	// Draw Calls
	// Draw Quad (x, y) (Color)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
		{ DrawQuad({position.x, position.y, 0.0}, size, color); }
	// Draw Quad (x, y, z) (Color)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		const float defualtWhiteTextureIndex = 0.0f;
		const float tilingFactor = 1.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		// (0, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[0];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[1];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[2];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (0, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[3];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadIndexCount += 6;
	}
	// Draw Quad (x, y) (Texture)
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
		{ DrawQuad({ position.x, position.y, 0.0 }, size, texture, tilingFactor, tintColor); }
	// Draw Quad (x, y, z) (Texture)
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
		{
			if (*rendererData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)rendererData.TextureSlotIndex;
			rendererData.TextureSlots[rendererData.TextureSlotIndex] = texture;
			rendererData.TextureSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		// (0, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[0];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[1];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[2];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (0, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[3];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadIndexCount += 6;
	}
	// Draw Rotated Quad (x, y) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
		{ DrawRotatedQuad({position.x, position.y, 0.0}, size, rotation, color); }
	// Draw Rotated Quad (x, y, z) (Color)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		XPROFILE_FUNCTION();
		const float defualtWhiteTextureIndex = 0.0f;
		const float tilingFactor = 1.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		// (0, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[0];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[1];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[2];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (0, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[3];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = defualtWhiteTextureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadIndexCount += 6;
	}
	// Draw Rotated Quad (x, y) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
		{ DrawRotatedQuad({ position.x, position.y, 0.0 }, size, rotation, texture, tilingFactor, tintColor); }
	// Draw Rotated Quad (x, y, z) (Texture)
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		XPROFILE_FUNCTION();
		constexpr glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		float textureIndex = 0.0f;
		for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++)
		{
			if (*rendererData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f)
		{
			textureIndex = (float)rendererData.TextureSlotIndex;
			rendererData.TextureSlots[rendererData.TextureSlotIndex] = texture;
			rendererData.TextureSlotIndex++;
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		// (0, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[0];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 0)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[1];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (1, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[2];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		// (0, 1)
		rendererData.QuadVertexBufferPtr->Position = transform * rendererData.QuadVertexPositions[3];
		rendererData.QuadVertexBufferPtr->Color = color;
		rendererData.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		rendererData.QuadVertexBufferPtr->TexIndex = textureIndex;
		rendererData.QuadVertexBufferPtr->TillingFactor = tilingFactor;
		rendererData.QuadVertexBufferPtr++;
		rendererData.QuadIndexCount += 6;
	}
}