// X-Engine Library Files
#include <XEngine.h>
#include "imgui/imgui.h"
// X Layer Class(Derived from Layer Class): Created new layer to push
class XLayer : public XEngine::Layer
{
public:
	int framesAlive;
	// Constructor: Logs creation
	XLayer() : Layer("X-Layer") 
	{ 
		XCLIENT_INFO("X-Layer Created"); 
		framesAlive = 0;
	}
	virtual ~XLayer()
	{
		XCLIENT_INFO("X-Layer was alive for {0} frames", framesAlive);
		XCLIENT_INFO("X-Layer Deleted");
	}
	// On Update Function(Override): Called every frame
	void OnUpdate() override 
	{ 
		framesAlive++;
		//XCLIENT_INFO("X-Layer has been alive for {0} frames", framesAlive);
	}
	// On ImGui Render Function(Override): ImGui Window, customize with ImGui functions
	virtual void OnImGuiRender() override
	{
		// Using ImGui namespace
		using namespace ImGui;
		// ---IMGUI CODE---
		// ----------------
	}
	// On Event Function(Override): Logs events when they happen
	virtual void OnAttach() { /*XCORE_ERROR("Attached");*/ }
	virtual void OnEvent(XEngine::Event& event) override { /*XCLIENT_TRACE("{0}", event);*/ }
};
// Game Class(Derived from Application Class)
class Game : public XEngine::Application
{
public:
	// Constructor: Pushes X Layer on creation
	Game() 
	{ 
		XCLIENT_INFO("Game Created");
		PushLayer(new XLayer()); 
	}
	// Destructor: Logs deletion
	~Game() { XCLIENT_INFO("Game Deleted"); }
};
// Using Application Class from XEngine namespace, to override the Create Application function
XEngine::Application* XEngine::CreateApplication() { return new Game(); }