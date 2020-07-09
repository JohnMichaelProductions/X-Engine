#include "Xpch.h"
#include "Renderer.h"
#include "../Shader.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
namespace XEngine
{
	Renderer::SceneData* Renderer::rendererSceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthographicCamera& camera) 
		{ rendererSceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix(); }
	void Renderer::EndScene() {}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", rendererSceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}