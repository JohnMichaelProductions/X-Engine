#pragma once
#include "RendererAPI.h"
namespace XEngine
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
			{ instanceRendererAPI->SetClearColor(color); }
		inline static void Clear()
			{ instanceRendererAPI->Clear(); }
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
			{ instanceRendererAPI->DrawIndexed(vertexArray); }
	private:
		static RendererAPI* instanceRendererAPI;
	};
}