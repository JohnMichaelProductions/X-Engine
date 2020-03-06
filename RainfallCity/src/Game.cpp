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
	// Constructor: If constructor bool is true then
	// print Game Created
	Game(bool constructorOn)
	{ 
		if (constructorOn == true)
			PushLayer(new XLayer());
	}
	// Destructor: Print Game Deleted
	~Game() { printf("Game Deleted\n"); }
};
// Creating the application, and returns a new game(app)
XEngine::Application* XEngine::CreateApplication() { return new Game(true); }