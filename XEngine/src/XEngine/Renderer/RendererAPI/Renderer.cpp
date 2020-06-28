#include "Xpch.h"
#include "Renderer.h"
#include "../Shader.h"
namespace XEngine
{
	Renderer::SceneData* Renderer::rendererSceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera) 
	{
		rendererSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene() {}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", rendererSceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}