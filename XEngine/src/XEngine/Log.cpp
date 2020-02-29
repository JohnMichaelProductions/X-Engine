#pragma region INCLUDE / NAMESPACES
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma endregion
namespace XEngine
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	#pragma region INIT FUNCTION
	void Log::Init()
	{
		// Setting up pattern for logging
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("X-Engine");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
	#pragma endregion
}