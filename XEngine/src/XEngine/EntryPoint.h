#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	// ---ENTRY POINT---						// ---ENTRY POINT---
	printf("Starting X-Engine\n");				// Start
	XEngine::Log::Init();						// Run Logging Inialization
	auto app = XEngine::CreateApplication();	// Create app
	app->Run();									// Running Application
	delete app;									// Delete app
}
#endif