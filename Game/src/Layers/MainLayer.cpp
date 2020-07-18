#include "ImGui/imgui.h"
#include "Layers/MainLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
MainLayer::MainLayer() : Layer("Main Layer"), mainCamera(1920.0f / 1080.0f) {}
void MainLayer::OnAttach()
	{ checkerboardTexture = XEngine::Texture2D::Create("Assets/Textures/Checkerboard.png"); }
void MainLayer::OnDetach() {}
void MainLayer::OnUpdate(XEngine::Timestep timestep)
{
	mainCamera.OnUpdate(timestep);
	// Background and clear
	XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
	XEngine::RenderCommand::Clear();
	// Draw command
	XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
	XEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	XEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, checkerboardTexture);
	XEngine::Renderer2D::EndScene();
}
void MainLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(mainColor));
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }