#include <XEngine.h>
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("X-Layer")
	{ 
		XCORE_INFO("X-Layer Created"); 
		memberDebugName = "X-Layer";
	}
	void OnUpdate() override
		{ XCORE_INFO("X-Layer Update"); }
	virtual void OnImGuiRender() override
		{ XCORE_INFO("ImGui Renderered on X-Layer"); }
	void OnEvent(XEngine::Event& event) override
		{ XCLIENT_TRACE("X-Layer Event: {0}", event); } 	
};
class Game : public XEngine::Application
{
public:
	Game()
	{
		XCORE_INFO("Game starting");
		PushLayer(new XLayer());
	}
	~Game()
		{ XCORE_INFO("Game shutting down!"); }
};
XEngine::Application* XEngine::CreateApplication()
	{ return new Game(); }