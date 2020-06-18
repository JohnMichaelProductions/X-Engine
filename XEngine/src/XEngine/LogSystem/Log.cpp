// Sets up logging system with Init function
#include "Xpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace XEngine
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("X-Engine");
		clientLogger = spdlog::stdout_color_mt("App");
		XCORE_INFO("Logging System initializated");	
	}
}