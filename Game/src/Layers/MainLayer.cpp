#include "ImGui/imgui.h"
#include "Layers/MainLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
MainLayer::MainLayer() : Layer("Main Layer"), mainCamera(1920.0f / 1080.0f) {}
void MainLayer::OnAttach() {}
void MainLayer::OnDetach() {}
void MainLayer::OnUpdate(XEngine::Timestep timestep)
{
	mainCamera.OnUpdate(timestep);
	// Background and clear
	XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	XEngine::RenderCommand::Clear();
	// Draw command
	XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
	XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { .8f, .2f, .3f, 1.0f });
	XEngine::Renderer2D::EndScene();
	//std::dynamic_pointer_cast<XEngine::OpenGLShader>(mainShader)->Bind();
	//std::dynamic_pointer_cast<XEngine::OpenGLShader>(mainShader)->UploadUniformFloat4("u_Color", mainColor);
}
void MainLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(mainColor));
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }