// Editor Layer Header file
#pragma once
#include <XEngine.h>
#include "Panels/Hierarchy.h"
namespace XEngine
{
	class EditorLayer : public Layer
	{
		public:
			EditorLayer();
			virtual ~EditorLayer() = default;
			virtual void OnAttach() override;
			virtual void OnDetach() override;
			void OnUpdate(Timestep timestep) override;
			virtual void OnImGuiRender() override;
			void OnEvent(Event& e) override;
		private:
			// Entities and Scene
			Ref<Scene> m_ActiveScene;
			Entity m_CameraEntity;
			Entity m_Ground;
			// Textures
			Ref<Texture2D> m_PlayerTexture;
			Ref<Texture2D> m_GroundTexture;
			Ref<Texture2D> m_BoundsTexture;
			Ref<Texture2D> m_OuterboundsTexture;
			// Camera
			OrthographicCameraController m_Camera;
			// Framebuffer and Viewport
			Ref<Framebuffer> m_Framebuffer;
			glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
			bool m_ViewportFocused = false, m_ViewportHovered = false;
			// Panels
			Hierarchy m_Hierarchy;
	};
}