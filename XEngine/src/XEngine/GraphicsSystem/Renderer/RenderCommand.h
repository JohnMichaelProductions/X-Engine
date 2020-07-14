#pragma once
#include "XEngine/GraphicsSystem/Renderer/RendererAPI.h"
namespace XEngine
{
	class RenderCommand
	{
	public:
		inline static void Init()
			{ renderCommandAPI->Init(); }
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
			{ renderCommandAPI->SetViewport(x, y, width, height); }
		inline static void SetClearColor(const glm::vec4& color)
			{ renderCommandAPI->SetClearColor(color); }
		inline static void Clear()
			{ renderCommandAPI->Clear(); }
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
			{ renderCommandAPI->DrawIndexed(vertexArray); }
		inline static void Documentation()
			{ renderCommandAPI->Documentation(); }
	private:
		static Scope<RendererAPI> renderCommandAPI;
	};
}