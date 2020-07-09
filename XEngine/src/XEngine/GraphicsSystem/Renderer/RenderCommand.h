#pragma once
#include "RendererAPI.h"
namespace XEngine
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
			{ renderCommandAPI->SetClearColor(color); }
		inline static void Clear()
			{ renderCommandAPI->Clear(); }
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
			{ renderCommandAPI->DrawIndexed(vertexArray); }
		inline static void Documentation()
			{ renderCommandAPI->Documentation(); }
	private:
		static RendererAPI* renderCommandAPI;
	};
}