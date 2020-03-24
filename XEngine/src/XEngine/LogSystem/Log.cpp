#include "Xpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace XEngine
{
	std::shared_ptr<spdlog::logger> Log::coreLogger;			// coreLogger Variable from Log.h
	std::shared_ptr<spdlog::logger> Log::clientLogger;			// clientLogger Variable from Log.h
	void Log::Init()											// Inialization Function: Initializes spdlog
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");					// Set Pattern for loggers
		coreLogger = spdlog::stdout_color_mt("X-Engine");		// Set coreLoggers name to X-Engine
		clientLogger = spdlog::stdout_color_mt("App");			// Set clientLoggers name to App
		XCORE_INFO("Logging System initializated");				// Log initialization
	}
}