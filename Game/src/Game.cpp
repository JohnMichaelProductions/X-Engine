// Where the game source code is written, stored, and called
#include "XEngine.h"
#include "XEngine/Core/EntryPoint.h"
#include "Layers/Xlayer.h"
#include "Layers/UILayer.h"
#include "Layers/MainLayer.h"
class Game : public XEngine::Application
{
public:
	Game()
	{ 
		XCORE_INFO("Game starting");
		PushLayer(new MainLayer());
	}
	~Game()
		{ XCORE_INFO("Game shutting down"); }
};
XEngine::Application* XEngine::CreateApplication()
	{ return new Game(); }