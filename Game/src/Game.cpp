#include <XEngine.h>
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer") {}
	void OnUpdate() override { X_INFO("XLayer::Update"); }
	void OnEvent(XEngine::Event& event) override { X_TRACE("{0}", event); }
};
class Game : public XEngine::Application
{
public:
	Game()
	{ 
		PushLayer(new XLayer());
		PushOverlay(new XEngine::ImGuiLayer());
	}
	// Destructor: Print Game Deleted
	~Game() { printf("Game Deleted\n"); }
};
// Creating the application, and returns a new game(app)
XEngine::Application* XEngine::CreateApplication() { return new Game(); }