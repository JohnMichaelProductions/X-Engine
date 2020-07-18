// Renderer 2D(Full static class)
#pragma once
#include "XEngine/GraphicsSystem/Camera.h"
#include "XEngine/GraphicsSystem/Texture.h"
namespace XEngine
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);
	};
}