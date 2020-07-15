#include "ImGui/imgui.h"
#include "Layers/MainLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
MainLayer::MainLayer() : Layer("Main Layer"), mainCamera(1920.0f / 1080.0f) {}
void MainLayer::OnAttach()
{
	mainVertexArray = XEngine::VertexArray::Create();
	float squareVertices[5 * 4] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	std::shared_ptr<XEngine::VertexBuffer> squareVB;
	squareVB.reset(XEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout
	({ { XEngine::ShaderDataType::Float3, "a_Position" } });
	mainVertexArray->AddVertexBuffer(squareVB);
	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	XEngine::Ref<XEngine::IndexBuffer> squareIB;
	squareIB.reset(XEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	mainVertexArray->SetIndexBuffer(squareIB);
	mainShader = XEngine::Shader::Create("Assets/Shaders/Square.shader");
}
void MainLayer::OnDetach() {}
void MainLayer::OnUpdate(XEngine::Timestep timestep)
{
	mainCamera.OnUpdate(timestep);
	// Background and clear
	XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	XEngine::RenderCommand::Clear();
	// Draw command
	XEngine::Renderer::BeginScene(mainCamera.GetCamera());
	std::dynamic_pointer_cast<XEngine::OpenGLShader>(mainShader)->Bind();
	std::dynamic_pointer_cast<XEngine::OpenGLShader>(mainShader)->UploadUniformFloat4("u_Color", mainColor);
	XEngine::Renderer::Submit(mainVertexArray, mainShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	XEngine::Renderer::EndScene();
}
void MainLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(mainColor));
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }