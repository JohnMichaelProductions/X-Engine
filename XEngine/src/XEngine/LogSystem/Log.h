// Header file for log system, also macro setup for logging
#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "../XCore.h"
namespace XEngine
{
	class XENGINE_API Log
	{
	public:
		// Defined in Source File
		static void Init();
		// Prototype in Header File
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
			{ return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
			{ return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}
#define XCORE_TRACE(...)::XEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XCORE_INFO(...)::XEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XCORE_WARN(...)::XEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XCORE_ERROR(...)::XEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XCORE_CRITICAL(...)::XEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define XCLIENT_TRACE(...)::XEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XCLIENT_INFO(...)::XEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define XCLIENT_WARN(...)::XEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XCLIENT_ERROR(...)::XEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define XCLIENT_CRITICAL(...)::XEngine::Log::GetClientLogger()->critical(__VA_ARGS__)