#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
int main(int argc, char** argv)
{
	printf("Welcome to X-Engine");
	auto app = XEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif