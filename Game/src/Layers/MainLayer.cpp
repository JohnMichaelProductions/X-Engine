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
	// Background and clear
	{
		XPROFILE_SCOPE("Renderer Preperation");
		XEngine::RenderCommand::SetClearColor({ .1f, .1f, .1f, 1 });
		XEngine::RenderCommand::Clear();
	}
	// Draw command
	{
		XPROFILE_SCOPE("Renderer Draw");
		// columns
		unsigned static int rows = 2;
		unsigned static int columns = 1;
		XCORE_INFO(rows);
		if (XEngine::Input::IsKeyPressed(XEngine::KeyCode::Right))
			rows++;
		if (XEngine::Input::IsKeyPressed(XEngine::KeyCode::Up))
			columns++;
		XEngine::Renderer2D::BeginScene(mainCamera.GetCamera());
		for (int i = 0; i < rows; i++)
		{
			XEngine::Renderer2D::DrawQuad({ (float)i, 0.0f, }, { .9f, .9f }, { .8f, .2f, .3f, 1.0f });
			for (int i = 0; i < columns; i++)
				XEngine::Renderer2D::DrawQuad({ 0.0f, (float)i, }, { .9f, .9f }, { .8f, .2f, .3f, 1.0f });
		}
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