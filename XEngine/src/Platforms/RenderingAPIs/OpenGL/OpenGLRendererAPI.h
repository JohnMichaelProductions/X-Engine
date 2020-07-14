// Header file for OpenGL Specific RenderAPI
#pragma once
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
namespace XEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		// Defined in Source File
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void Documentation() override;
	};
}