// Renderer API for OpenGL(as of now)
#pragma once
#include <glm/glm.hpp>
#include "XEngine/GraphicsSystem/VertexArray.h"
namespace XEngine
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void Documentation() = 0;
		static Scope<RendererAPI> Create();
		// Prototype in Header File
		inline static API GetAPI()
			{ return renderAPI; }
	private:
		static API renderAPI;
	};
}

