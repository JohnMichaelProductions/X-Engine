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
	logoTexture = XEngine::Texture2D::Create("Assets/Textures/ChernoLogo.png");
}
void MainLayer::OnDetach()
	{ XPROFILE_FUNCTION(); }
void MainLayer::OnUpdate(XEngine::Timestep timestep)
{
	XPROFILE_FUNCTION();
	mainCamera.OnUpdate(timestep);
	XEngine::Renderer2D::ResetStats();
	// Background and clear
	{
		XPROFILE_SCOPE("Renderer Preperation");
		XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		XEngine::RenderCommand::Clear();
	}
	// Draw command
	{
		XPROFILE_SCOPE("Renderer Draw");
		static float rotation = 0.0f;
		rotation += timestep * 50.0f;
		XPROFILE_SCOPE("Renderer Draw");
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		XEngine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, checkerboardTexture, 10.0f);
		XEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, checkerboardTexture, 20.0f);
		XEngine::Renderer2D::EndScene();
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				XEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		XEngine::Renderer2D::EndScene();
	}
}
void MainLayer::OnImGuiRender()
{
	XPROFILE_FUNCTION();
	auto stats = XEngine::Renderer2D::GetStats();
	ImGui::Begin("Profiler");
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }