// Entry Point of X-Engine
#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	printf("-----Starting X-Engine-----\n");
	XEngine::Logging::Init();
	auto app = XEngine::CreateApplication();
	app->Run();
	delete app;
	printf("-----X-Engine Shutdown-----");
}
#endif