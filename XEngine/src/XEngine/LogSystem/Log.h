#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "../XCore.h"
namespace XEngine
{
	class XENGINE_API Log
	{
	public:
		static void Init();													// Inialization Function: Initializes spdlog
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()		// Get Core Logger Function: Returns coreLogger Variable
			{ return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()	// Get Client Logger Function: Returns clientLogger Variable
			{ return clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> coreLogger;					// spdlog logger variable, for core logging
		static std::shared_ptr<spdlog::logger> clientLogger;				// spdlog logger variable, for client logging
	};
}
// ---MACROS---
#define XCORE_TRACE(...)		::XEngine::Log::GetCoreLogger	()->trace(__VA_ARGS__)	// Trace Core Logging
#define XCORE_INFO(...)			::XEngine::Log::GetCoreLogger	()->info(__VA_ARGS__)	// Info Core Logging
#define XCORE_WARN(...)			::XEngine::Log::GetCoreLogger	()->warn(__VA_ARGS__)	// Warn Core Logging
#define XCORE_ERROR(...)		::XEngine::Log::GetCoreLogger	()->error(__VA_ARGS__)	// Error Core Logging
#define XCORE_FATAL(...)		::XEngine::Log::GetCoreLogger	()->fatal(__VA_ARGS__)	// Fatal Core Logging
#define XCLIENT_TRACE(...)		::XEngine::Log::GetClientLogger	()->trace(__VA_ARGS__)	// Trace Client Logging
#define XCLIENT_INFO(...)		::XEngine::Log::GetClientLogger	()->info(__VA_ARGS__)	// Info Client Logging
#define XCLIENT_WARN(...)		::XEngine::Log::GetClientLogger	()->warn(__VA_ARGS__)	// Warn Client Logging
#define XCLIENT_ERROR(...)		::XEngine::Log::GetClientLogger	()->error(__VA_ARGS__)	// Error Client Logging
#define XCLIENT_FATAL(...)		::XEngine::Log::GetClientLogger	()->fatal(__VA_ARGS__)	// Fatal Client Logging
// -----------