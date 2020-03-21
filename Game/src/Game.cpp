// X-Engine Library Files
#include <XEngine.h>
// ImGui Library Files
#include "vendor/imgui/imgui.h"
// X Layer Class(Derived from Layer Class)
class XLayer : public XEngine::Layer
{
public:
	// Constructor
	XLayer() : Layer("X-Layer") { XCORE_INFO("X-Layer Created"); }
	// On Update Function(Override from Layer Class): Called every frame
	void OnUpdate() override { /*XCORE_INFO("X-Layer Update");*/ }
	// On ImGui Render Function(Override from Layer Class): ImGui Window, customize with ImGui functions
	virtual void OnImGuiRender() override
	{
		using namespace ImGui;
		// ---Write ImGui Code Here!---
		//
		//
		//
		// ----------------------------
	}
	// On Event Function(Override from Layer Class): Logs events when they happen
	void OnEvent(XEngine::Event& event) override { /*XCLIENT_TRACE("{0}", event);*/ }
};
// Game Class(Derived from Application Class
class Game : public XEngine::Application
{
public:
	// Constructor
	Game() 
	{
		XCORE_INFO("New Game(Class) has been created!");
		// Pushes X-Layer 
		PushLayer(new XLayer()); 
	}
	// Destructor
	~Game() { XCORE_INFO("Game(Class) has been destroyed!"); }
};
// Using Application Class from XEngine namespace, to override the Create Application function
XEngine::Application* XEngine::CreateApplication() { return new Game(); }