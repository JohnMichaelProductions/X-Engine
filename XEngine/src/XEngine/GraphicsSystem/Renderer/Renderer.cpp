#include "Xpch.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer2D.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
namespace XEngine
{
	Scope<Renderer::SceneData> Renderer::rendererSceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{ 
		RenderCommand::Init(); 
		Renderer2D::Init();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
		{ RenderCommand::SetViewport(0, 0, width, height); }
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