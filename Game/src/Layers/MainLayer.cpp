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
	XEngine::Renderer2D::ResetStats();
	// Background and clear
	{
		XPROFILE_SCOPE("Renderer Preperation");
		XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		XEngine::RenderCommand::Clear();
	}
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
}
void MainLayer::OnImGuiRender()
{
	XPROFILE_FUNCTION();
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->GetWorkPos());
		ImGui::SetNextWindowSize(viewport->GetWorkSize());
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);
	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) XEngine::Application::Get().Close();
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	auto stats = XEngine::Renderer2D::GetStats();
	ImGui::Begin("Profiler");
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	uint32_t textureID = checkerboardTexture->GetRendererID();
	ImGui::Image((void*)textureID, ImVec2{256.0f, 256.0f});
	ImGui::End();
	ImGui::End();
}
void MainLayer::OnEvent(XEngine::Event& e)
	{ mainCamera.OnEvent(e); }