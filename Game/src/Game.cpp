#include <XEngine.h>
#include "imgui/imgui.h"
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer") {}
	void OnUpdate() override {}
	virtual void OnImGuiRender() override
	{
		using namespace ImGui;
		Begin("Test");
		Text("Hello World");
		End();
	}
	void OnEvent(XEngine::Event& event) override { XCLIENT_TRACE("{0}", event); }
};
class Game : public XEngine::Application
{
public:
	Game() {  PushLayer(new XLayer()); }
	// Destructor: Print Game Deleted
	~Game() { printf("Game Deleted\n"); }
};
// Creating the application, and returns a new game(app)
XEngine::Application* XEngine::CreateApplication() { return new Game(); }