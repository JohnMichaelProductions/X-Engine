#include <stdio.h>
#include "Application.h"
#include "../XEngine/EventSystem/ApplicationEvent.h"
#include "../XEngine/Log.h"
namespace XEngine
{
	Application::Application() { printf("Application Created\n"); }
	Application::~Application() { printf("Application Deleted\n"); }
	void Application::Run() 
	{
		WindowResizeEvent test(1920, 1080);
		if (test.IsInCategory(EventCategoryApplication))
			X_TRACE(test);
		else
			X_ERROR("Variable: \"test\" is not in the Application Event Category");
		while(true); 
	}
}