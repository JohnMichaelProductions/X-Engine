#include <XEngine.h>
class Game : public XEngine::Application
{
public:
	Game(){}
	~Game(){}
};
XEngine::Application* XEngine::CreateApplication() { return new Game(); }