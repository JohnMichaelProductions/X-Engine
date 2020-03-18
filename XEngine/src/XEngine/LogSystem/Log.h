#pragma once
// spdlog Library Files
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
// Mid Files
#include "../XCore.h"
namespace XEngine
{
	class XENGINE_API Log
	{
	public:
		// ---FUNCTIONS---
		// Init Function: Initialize Loggers 
		static void Init();
		// Get Core Logger Function: Returns core logger
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		// Get Client Logger Function: Returns client logger
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
		// ---------------
	private:
		// Core Logger Variable
		static std::shared_ptr<spdlog::logger> coreLogger;
		// Client Logger Variable
		static std::shared_ptr<spdlog::logger> clientLogger;
	};
}
// Macros: Logging
#define XCORE_TRACE(...)		::XEngine::Log::GetCoreLogger	()->trace(__VA_ARGS__)
#define XCORE_INFO(...)			::XEngine::Log::GetCoreLogger	()->info(__VA_ARGS__)
#define XCORE_WARN(...)			::XEngine::Log::GetCoreLogger	()->warn(__VA_ARGS__)
#define XCORE_ERROR(...)		::XEngine::Log::GetCoreLogger	()->error(__VA_ARGS__)
#define XCORE_FATAL(...)		::XEngine::Log::GetCoreLogger	()->fatal(__VA_ARGS__)
#define XCLIENT_TRACE(...)		::XEngine::Log::GetClientLogger	()->trace(__VA_ARGS__)
#define XCLIENT_INFO(...)		::XEngine::Log::GetClientLogger	()->info(__VA_ARGS__)
#define XCLIENT_WARN(...)		::XEngine::Log::GetClientLogger	()->warn(__VA_ARGS__)
#define XCLIENT_ERROR(...)		::XEngine::Log::GetClientLogger	()->error(__VA_ARGS__)
#define XCLIENT_FATAL(...)		::XEngine::Log::GetClientLogger	()->fatal(__VA_ARGS__)