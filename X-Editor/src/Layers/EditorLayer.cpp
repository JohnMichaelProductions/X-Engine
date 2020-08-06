// Editor Layer Source file
#include <chrono>
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "Layers/EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
namespace XEngine
{
	EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Camera(1920.0f / 1080.0f) {}
	void EditorLayer::OnAttach()
	{
		// Creating Checkerboard Texture
		XPROFILE_FUNCTION();
		m_CheckerboardTexture = XEngine::Texture2D::Create("Assets/Textures/Checkerboard.png");
		XEngine::FramebufferSpecificaion fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = XEngine::Framebuffer::Create(fbSpec);
	}
	void EditorLayer::OnDetach()
		{ XPROFILE_FUNCTION(); }
	void EditorLayer::OnUpdate(XEngine::Timestep timestep)
	{
		XPROFILE_FUNCTION();
		if(m_ViewportFocused)
			m_Camera.OnUpdate(timestep);
		XEngine::Renderer2D::ResetStats();
		// Background and clear
		{
			XPROFILE_SCOPE("Renderer Preperation");
			m_Framebuffer->Bind();
			XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
			XEngine::RenderCommand::Clear();
		}
		// Draw
		{
			XPROFILE_SCOPE("Renderer Draw");
			XEngine::Renderer2D::BeginScene(m_Camera.GetCamera());
			XEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
			for (float y = -5.0f; y < m_GridSize.y; y += 0.5f)
			{
				for (float x = -5.0f; x < m_GridSize.x; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
					XEngine::Renderer2D::DrawQuad({ x, y, 0.0F }, { 0.45f, 0.45f }, color);
				}
			}
			XEngine::Renderer2D::EndScene();
			m_Framebuffer->Unbind();
		}
	}
	void EditorLayer::OnImGuiRender()
	{
		XPROFILE_FUNCTION();
		// Dockspace
		{
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
			ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();
			if (opt_fullscreen)
				ImGui::PopStyleVar(2);
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("DockSpace");
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
			// Viewport
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
				ImGui::Begin("Viewport");
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
				if (m_ViewportSize != *((glm::vec2*) & viewportPanelSize))
				{
					m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
					m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
					m_Camera.OnResize(viewportPanelSize.x, viewportPanelSize.y);
				}
				uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
				ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
				ImGui::End();
				ImGui::PopStyleVar();
			}
			// Profiler
			{
				ImGui::Begin("Profiler");
				ImGui::Text("Renderer2D Stats: ");
				ImGui::Text("Draw Calls: %d", stats.DrawCalls);
				ImGui::Text("Quads: %d", stats.QuadCount);
				ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
				ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
				ImGui::End();
			}
			// Scene Settings
			{
				ImGui::Begin("Scene Settings");
				ImVec2 gridSize = { m_GridSize.x, m_GridSize.y };
				ImGui::DragFloat2("Grid Size", (float*)&gridSize);
				m_GridSize = { gridSize.x, gridSize.y };
				ImGui::End();
			}
			// ImGui Settings
			{
				ImGui::Begin("ImGui Settings");
				ImGui::ShowFontSelector("Fonts");
				//ImGui::Checkbox("Block ImGui Layer Events", ImGuiLayer.SetBlockEvents())
				ImGui::End();
			}
			// File Manager
			{

			}
			ImGui::End();
		}
	}
	void EditorLayer::OnEvent(Event& e)
		{ m_Camera.OnEvent(e); }
}