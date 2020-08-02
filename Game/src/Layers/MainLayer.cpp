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
	spriteSheet = XEngine::Texture2D::Create("Assets/Game/Textures/Tilemap.png");
	treeTexture = XEngine::SubTexture2D::CreateFromCoords(spriteSheet, { 2, 1 }, { 128, 128 }, { 1, 2 });
	// Particle Properties
	mainParticle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	mainParticle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	mainParticle.SizeBegin = 0.5f, mainParticle.SizeVariation = 0.3f, mainParticle.SizeEnd = 0.0f;
	mainParticle.LifeTime = 5.0f;
	mainParticle.Velocity = { 0.0f, 0.0f };
	mainParticle.VelocityVariation = { 3.0f, 1.0f };
	mainParticle.Position = { 0.0f, 0.0f };
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
	#if 0
	{
		XPROFILE_SCOPE("Renderer Draw");
		static float rotation = 0.0f;
		rotation += timestep * 50.0f;
		XPROFILE_SCOPE("Renderer Draw");
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		XEngine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f, 0.0f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, checkerboardTexture, 10.0f);
		XEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.5f }, { 1.0f, 1.0f }, glm::radians(rotation), checkerboardTexture, 20.0f);
		XEngine::Renderer2D::EndScene();
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				XEngine::Renderer2D::DrawQuad({ x, y, 0.0F }, { 0.45f, 0.45f }, color);
			}
		}
		XEngine::Renderer2D::EndScene();
	}
	#endif
	if (XEngine::Input::IsMouseButtonPressed(XEngine::MouseCode::ButtonLeft))
	{
		auto [x, y] = XEngine::Input::GetMousePosition();
		auto width = XEngine::Application::Get().GetWindow().GetWidth();
		auto height = XEngine::Application::Get().GetWindow().GetHeight();
		auto bounds = mainCamera.GetBounds();
		auto pos = mainCamera.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		mainParticle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			mainParticleSystem.Emit(mainParticle);
	}
	XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
	XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f }, treeTexture);
	XEngine::Renderer2D::EndScene();
	mainParticleSystem.OnUpdate(timestep);
	mainParticleSystem.OnRender(mainCamera.GetCamera());
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