#pragma once
#include "XCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace XEngine
{
	class XENGINE_API Log
	{
	public:
		// Create Initialization function
		static void Init();
		// Core and Client Logger
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		// Core and Client Logger
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
// Defining loggers
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