#include "Xpch.h"
#include "XEngine/Application.h"
#include "Win10Input.h"
#include <GLFW/glfw3.h>
namespace XEngine
{
	// Input Variable(New Win10Input Class)
	Input* Input::inputInstance = new Win10Input();
	// Is Key Pressed Impl Function: Implementation Function, Return true if a key is pressed, gets key and returns the pressed or repeat state
	bool Win10Input::IsKeyPressedImpl(int keycode)
	{
		// Local Variable Window: Gets Window to use in the glfwGetKey Function
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets state
		auto state = glfwGetKey(window, keycode);
		// Returns state
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	// Is Mouse Button Pressed Impl Function: Implementation Function, Return true if a mouse button is pressed, gets button and returns the pressed state
	bool Win10Input::IsMouseButtonPressedImpl(int button)
	{
		// Local Variable Window: Gets Window to use in the glfwGetMouseButton Function
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Gets state
		auto state = glfwGetMouseButton(window, button);
		// Returns state
		return state == GLFW_PRESS;
	}
	// Get Mouse Position Impl Function: Implementation Function, Returns Mouse Position(x, y)
	std::pair<float, float> Win10Input::GetMousePositionImpl()
	{
		// Local Variable Window: Gets Window to use in the glfwGetCursorPos Function
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		// Local Variable x and y Pos
		double xPos, yPos;
		// Uses glfwGetCursorPos to get the x and y value using the window
		glfwGetCursorPos(window, &xPos, &yPos);
		// Returns two floats, x and y pos of mouse
		return { (float)xPos, (float)yPos };
	}
	// Get Mouse X Impl: Implementation Function, Calls GetMousePositionImpl function and returns the x value
	float Win10Input::GetMouseXImpl()
	{
		// Calls GetMousePositionImpl function as an auto variable
		auto [x, y] = GetMousePositionImpl();
		// Returns x variable of GetMousePositionImpl
		return x;
	}
	// Get Mouse Y Impl: Implementation Function, Calls GetMousePositionImpl function and returns the y value
	float Win10Input::GetMouseYImpl()
	{
		// Calls GetMousePositionImpl function as an auto variable
		auto [x, y] = GetMousePositionImpl();
		// Returns y variable of GetMousePositionImpl
		return y;
	}
}