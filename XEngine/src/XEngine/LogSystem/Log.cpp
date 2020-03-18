// Top Files
#include "Xpch.h"
// Log System Files
#include "Log.h"
// spdlog Library Files
#include "spdlog/sinks/stdout_color_sinks.h"
namespace XEngine
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;
	// Logging Library Initialization Function
	void Log::Init()
	{
		// Setting up pattern for logging
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// Setting up Core Logger
		coreLogger = spdlog::stdout_color_mt("X-Engine");
		coreLogger->set_level(spdlog::level::trace);
		// Setting up Client Logger
		clientLogger = spdlog::stdout_color_mt("Game");
		clientLogger->set_level(spdlog::level::trace);
		XCORE_INFO("Log System Initialized");
	}
}