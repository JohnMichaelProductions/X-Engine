// Sets up logging system with Init function
#include "Xpch.h"
#include "XEngine/LoggingSystem/Logging.h"
#include <spdlog/sinks/stdout_color_sinks.h>
namespace XEngine
{
	Ref<spdlog::logger> Logging::coreLogger;
	Ref<spdlog::logger> Logging::clientLogger;
	void Logging::Init()
	{
		#ifdef X_DEBUG
			spdlog::set_level(spdlog::level::trace);
		#endif
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("X-Engine");
		clientLogger = spdlog::stdout_color_mt("App");
		XCORE_INFO("Logging System initializated");
	}
}