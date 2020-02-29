#pragma once
#ifdef X_PLATFORM_WINDOWS
extern XEngine::Application* XEngine::CreateApplication();
#pragma region INITIALIZATION FUNCTION
void Initialization()
{
	// Start
	printf("X-Engine starting initialization\n");
	// Logging
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
	X_CORE_TRACE("Now using Logging system");
	// Pre-Compiled Headers
	X_CORE_TRACE("Using Pre-Compiled Headers");
	// Event System
	X_CORE_TRACE("Starting Event System");
	// Finish
	X_CORE_INFO("X-Engine initialization finished");
}
#pragma endregion
#pragma region MAIN FUNCTION
int main(int argc, char** argv)
{
	// Run Initialization function
	Initialization();
	// Create app
	auto app = XEngine::CreateApplication();
	// Keep it running
	app->Run();
	// Delete app
	delete app;
}
#pragma endregion
#endif