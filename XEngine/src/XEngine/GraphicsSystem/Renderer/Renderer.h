#pragma once
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "../Camera.h"
#include "../Shader.h"
namespace XEngine
{
	class Renderer
	{
	public:
		static void Init();
		static void BeginScene(OrthographicCamera& camera);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void EndScene();
		inline static RendererAPI::API GetAPI() 
			{ return RendererAPI::GetAPI(); }
	private:
		struct SceneData
			{ glm::mat4 ViewProjectionMatrix; };
		static SceneData* rendererSceneData;
	};
}