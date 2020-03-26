#include <XEngine.h>
class XLayer : public XEngine::Layer
{
public:														// {PUBLIC}
	XLayer() : Layer("X-Layer") 							// Constructor: Logs Creation
		{ XCORE_INFO("X-Layer Created"); }
	void OnUpdate() override								// (Override) On Update Function: Called every frame
		{ /*XCORE_INFO("X-Layer Update");*/ }
	virtual void OnImGuiRender() override					// (Virtual) (Override) On ImGui Render Function: ImGui Window, customize with ImGui functions
		{}
	void OnEvent(XEngine::Event& event) override			// (Override) On Event Function: Logs events when they happen
		{ /*XCLIENT_TRACE("{0}", event);*/ } 	
};
class Game : public XEngine::Application
{
public:														// {PUBLIC}
	Game()													// Constructor
	{
		XCORE_INFO("New Game(Class) has been created!");	// Logs creation
		PushLayer(new XLayer());							// Creates and pushes a new X-Layer
	}
	~Game()													// Destructor: Logs deletion
		{ XCORE_INFO("Game(Class) has been destroyed!"); }
};
XEngine::Application* XEngine::CreateApplication()			// Create Application Function: Creates and returns a Game
	{ return new Game(); }	