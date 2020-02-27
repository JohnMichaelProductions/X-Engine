#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
void Initialization()
{
	//Start
	printf("X-Engine starting initialization\n");
	//Logging
	printf("Preparing Logging system\n");
	XEngine::Log::Init();
	printf("Testing Core Logs\n");
	X_CORE_TRACE("Trace Core Test");
	X_CORE_INFO("Info Core Test");
	X_CORE_WARN("Warn Core Test");
	X_CORE_ERROR("Error Core Test");
	printf("Testing Client Logs\n");
	X_TRACE("Trace Client Test");
	X_INFO("Info Client Test");
	X_WARN("Warn Client Test");
	X_ERROR("Error Client Test");
	printf("Logging system working\n");
	//Finish
	printf("X-Engine initialization finished\n");
}
int main(int argc, char** argv)
{
	Initialization();
	auto app = XEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif