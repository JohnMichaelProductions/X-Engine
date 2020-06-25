// Where the game source code is written, stored, and called
#include <XEngine.h>
class Game : public XEngine::Application
{
public:
	Game()
		{ XCORE_INFO("Game starting"); }
	~Game()
		{ XCORE_INFO("Game shutting down!"); }
};
XEngine::Application* XEngine::CreateApplication()
	{ return new Game(); }