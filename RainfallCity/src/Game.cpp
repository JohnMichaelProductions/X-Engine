#pragma region INCLUDE / NAMESPACES
#include <XEngine.h>
#pragma endregion
#pragma region GAME CLASS
class Game : public XEngine::Application
{
public:
	// Constructor: If constructor bool is true then
	// print Game Created
	Game(bool constructorOn)
	{ 
		if(constructorOn == true)
			printf("Game Created\n"); 
	}
	// Destructor: Print Game Deleted
	~Game() { printf("Game Deleted\n"); }
};
#pragma endregion
// Creating the application, and returns a new game(app)
XEngine::Application* XEngine::CreateApplication() { return new Game(false); }