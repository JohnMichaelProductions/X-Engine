#pragma region INCLUDE / NAMESPACES
#include "Xpch.h"
#include <stdio.h>
#include "Application.h"
#include "../XEngine/EventSystem/ApplicationEvent.h"
#include "../XEngine/Log.h"
#pragma endregion
namespace XEngine
{
	// Constructor: Print Application Created
	Application::Application() { X_TRACE("Application Created"); }
	// Destructor: Print Application Deleted
	Application::~Application() { printf("Application Deleted\n"); }
	// Function: Keeps application alive and running
	#pragma region RUN FUNCTION
	void Application::Run() 
	{
		// New Window Resize Event
		WindowResizeEvent test(1920, 1080);
		// Log the variable test if it is an application event
		if (test.IsInCategory(EventCategoryApplication))
			X_TRACE(test);
		// Else error
		else
			X_ERROR("Variable: \"test\" is not in the Application Event Category");
		// Keeps the application running
		while(true); 
	}
	#pragma endregion
}