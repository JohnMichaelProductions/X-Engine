#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	// ---ENTRY POINT---
	printf("Starting X-Engine\n");
	// Run Logging Inialization
	XEngine::Log::Init();
	// Create app
	auto app = XEngine::CreateApplication();
	// Running Application
	app->Run();
	// Delete app
	delete app;
}
#endif