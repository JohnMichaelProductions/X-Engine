#include <XEngine.h>
#include "imgui/imgui.h"
// X Layer Class(Derived from Layer Class)
class XLayer : public XEngine::Layer
{
public:
	// Constructor: Logs creation
	XLayer() : Layer("XLayer") { XCORE_INFO("X-Layer Created"); }
	// On Update Function(Override): Called every frame
	void OnUpdate() override {}
	// On ImGui Render Function(Override): ImGui Window, customize with ImGui functions
	virtual void OnImGuiRender() override
	{
		// Using ImGui namespace
		using namespace ImGui;
		// ---Write ImGui Code Here!---
		//
		//
		//
		// ----------------------------
	}
	// On Event Function(Override): Logs events when they happen
	void OnEvent(XEngine::Event& event) override { XCLIENT_TRACE("{0}", event); }
};
// Game Class(Derived from Application Class
class Game : public XEngine::Application
{
public:
	// Constructor: Pushes X Layer on creation
	Game() {  PushLayer(new XLayer()); }
	// Destructor: Logs deletion
	~Game() { printf("Game Deleted\n"); }
};
// Using Application Class from XEngine namespace, to override the Create Application function
XEngine::Application* XEngine::CreateApplication() { return new Game(); }