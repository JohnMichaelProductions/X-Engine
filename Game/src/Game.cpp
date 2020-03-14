#include <XEngine.h>
#include "imgui/imgui.h"
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer") {}
	void OnUpdate() override {}
	void OnEvent(XEngine::Event& event) override { XCLIENT_TRACE("{0}", event); }
	/*virtual void OnImGuiRender() override
	{
		using namespace ImGui;
		Begin("Test");
		Text("Hello World");
		End();
	}*/
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