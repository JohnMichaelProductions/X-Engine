#include <XEngine.h>
class Game : public XEngine::Application
{
public:
	Game(bool constructorOn)
	{ 
		if(constructorOn == true)
			printf("Game Created\n"); 
	}
	~Game() { printf("Game Deleted\n"); }
};
XEngine::Application* XEngine::CreateApplication() { return new Game(false); }