#include <stdio.h>
#include "Application.h"
namespace XEngine
{
	Application::Application() { printf("Application Created\n"); }
	Application::~Application() { printf("Application Deleted\n"); }
	void Application::Run() { while(true); }
}