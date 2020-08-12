// Editor Layer Header file
#pragma once
#include <XEngine.h>
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
			Entity m_SquareEntity;
			Entity m_CameraEntity;
			Entity m_Checkerboard;
			// Textures
			Ref<Texture2D> m_CheckerboardTexture;
			// Camera
			OrthographicCameraController m_Camera;
			// Framebuffer and Viewport
			Ref<Framebuffer> m_Framebuffer;
			glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
			bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}