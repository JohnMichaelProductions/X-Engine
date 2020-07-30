#pragma once
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
namespace XEngine
{
	class RenderCommand
	{
	public:
		static void Init()
			{ renderCommandAPI->Init(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
			{ renderCommandAPI->SetViewport(x, y, width, height); }
		static void SetClearColor(const glm::vec4& color)
			{ renderCommandAPI->SetClearColor(color); }
		static void Clear()
			{ renderCommandAPI->Clear(); }
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
			{ renderCommandAPI->DrawIndexed(vertexArray, count); }
	private:
		static Scope<RendererAPI> renderCommandAPI;
	};
}