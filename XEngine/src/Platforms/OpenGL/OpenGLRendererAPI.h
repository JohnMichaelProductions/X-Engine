// Header file for OpenGL Specific RenderAPI
#pragma once
#include "XEngine/Renderer/RendererAPI/RendererAPI.h"
namespace XEngine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		// Defined in Source File
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		virtual void Documentation() override;
	};
}