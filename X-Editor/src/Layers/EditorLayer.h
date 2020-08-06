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
			// Temp
			OrthographicCameraController m_Camera;
			Ref<VertexArray> m_VertexArray;
			Ref<Shader> m_Shader;
			Ref<Framebuffer> m_Framebuffer;
			Ref<Texture2D> m_CheckerboardTexture;
			glm::vec2 m_GridSize = { 5.0f, 5.0f };
			glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
			glm::vec4 mainColor = { 0.2f, 0.3f, 0.8f, 1.0f };
			float m_Framerate = 0.0f;
			bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}