#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	//Run Logging Inialization
	XEngine::Log::Init();
	// Create app
	auto app = XEngine::CreateApplication();
	// Keep it running
	app->Run();
	// Delete app
	delete app;
}
#endif