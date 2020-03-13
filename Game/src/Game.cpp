#include <XEngine.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}
class XLayer : public XEngine::Layer
{
public:
	XLayer() : Layer("XLayer") {}
	void OnUpdate() override {}
	void OnEvent(XEngine::Event& event) override { XCLIENT_TRACE("{0}", event); }
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