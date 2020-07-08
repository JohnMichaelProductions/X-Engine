#include "Xpch.h"
#include "Renderer.h"
#include "../Shader.h"
namespace XEngine
{
	Renderer::SceneData* Renderer::rendererSceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera) 
		{ rendererSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); }
	void Renderer::EndScene() {}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", rendererSceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}