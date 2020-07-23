#include <chrono>
#include <ImGui/imgui.h>
#include "Layers/MainLayer.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
MainLayer::MainLayer() : Layer("Main Layer"), mainCamera(1920.0f / 1080.0f) {}
void MainLayer::OnAttach()
{
	// Creating Checkerboard Texture
	XPROFILE_FUNCTION();
	checkerboardTexture = XEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
}
void MainLayer::OnDetach()
	{ XPROFILE_FUNCTION(); }
void MainLayer::OnUpdate(XEngine::Timestep timestep)
{
	XPROFILE_FUNCTION();
	mainCamera.OnUpdate(timestep);
	// Background and clear
	{
		XPROFILE_SCOPE("Renderer Preperation");
		XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		XEngine::RenderCommand::Clear();
	}
	// Draw command
	{
		XPROFILE_SCOPE("Renderer Draw");
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		XEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, checkerboardTexture);
		XEngine::Renderer2D::EndScene();
	}
}
void MainLayer::OnImGuiRender()
{
	XPROFILE_FUNCTION();
	ImGui::Begin("Profiler");
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }