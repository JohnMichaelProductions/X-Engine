// Editor Layer Source file
#include <chrono>
#include <ImGui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "Layers/EditorLayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "XEngine/Debug/Instrumentor.h"
namespace XEngine
{
	EditorLayer::EditorLayer() : Layer("Editor Layer"), m_Camera(1920.0f / 1080.0f) {}
	void EditorLayer::OnAttach()
	{
		XPROFILE_FUNCTION();
		// Framebuffer
		FramebufferSpecificaion fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);
		m_PlayerTexture = Texture2D::Create("Assets/Textures/PlayerIdle.png");
		m_GroundTexture = Texture2D::Create("Assets/Textures/Ground.png");
		m_BoundsTexture = Texture2D::Create("Assets/Textures/Bounds.png");
		m_OuterboundsTexture = Texture2D::Create("Assets/Textures/OuterBounds.png");
		m_ActiveScene = CreateRef<Scene>();
		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();
		m_Ground = m_ActiveScene->CreateEntity("Ground");
		m_Ground.AddComponent<SpriteRendererComponent>().Texture = m_GroundTexture;
		m_Ground.GetComponent<SpriteRendererComponent>().TillingFactor = 10.0f;
		m_Ground.GetComponent<TransformComponent>().Size = { 10.0f, 10.0f };
		class Controller : public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				auto& transform = GetComponent<TransformComponent>();
				transform.Position.x = rand() % 10 - 5.0f;
			}
			void OnDestroy() {}
			void OnUpdate(Timestep timestep)
			{
				auto& transform = GetComponent<TransformComponent>().Position;
				float speed = 5.0f;
				if (Input::IsKeyPressed(Key::A))
					transform.x -= speed * timestep;
				if (Input::IsKeyPressed(Key::D))
					transform.x += speed * timestep;
				if (Input::IsKeyPressed(Key::W))
					transform.y += speed * timestep;
				if (Input::IsKeyPressed(Key::S))
					transform.y -= speed * timestep;
			}
		};
		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<Controller>();
		m_Hierarchy.SetContext(m_ActiveScene);
	}
	void EditorLayer::OnDetach()
		{ XPROFILE_FUNCTION(); }
	void EditorLayer::OnUpdate(Timestep timestep)
	{
		XPROFILE_FUNCTION();
		// Framebuffer
		if (FramebufferSpecificaion spec = m_Framebuffer->GetSpecificaion(); m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_Camera.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}
		if(m_ViewportFocused)
			m_Camera.OnUpdate(timestep);
		// Profiler
		Renderer2D::ResetStats();
		// Background and clear
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		RenderCommand::Clear();
		// Begin Scene and Draw
		m_ActiveScene->OnUpdate(timestep);
		m_Framebuffer->Unbind();
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
					if (ImGui::MenuItem("Exit")) Application::Get().Close();
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			auto stats = Renderer2D::GetStats();
			// Scene
			{
				ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
				ImGui::Begin("Scene");
				m_ViewportFocused = ImGui::IsWindowFocused();
				m_ViewportHovered = ImGui::IsWindowHovered();
				Application::Get().GetImGuiLayer()->SetBlockEvents(!m_ViewportFocused || !m_ViewportHovered);
				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();	
				m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
				uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
				ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
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
			// Hierarchy
				{ m_Hierarchy.OnImGuiRender(); }
			// Inspector
				{ m_Properties.OnImGuiRender(m_Hierarchy.m_SelectionContext); }
			ImGui::End();
		}
	}
	void EditorLayer::OnEvent(Event& e)
		{ m_Camera.OnEvent(e); }
}