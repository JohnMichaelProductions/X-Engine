#pragma once
#include <mutex>
#include <chrono>
#include <string>
#include <thread>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "XEngine/LoggingSystem/Logging.h"
namespace XEngine
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;
	struct ProfileResult
	{
		std::string name;
		FloatingPointMicroseconds start;
		std::chrono::microseconds elapsedTime;
		std::thread::id threadID;
	};
	struct InstrumentationSession
		{ std::string name; };
	class Instrumentor
	{
	public:
		Instrumentor() : instrumentorCurrentSession(nullptr) {}
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(instrumentorMutex);
			if (instrumentorCurrentSession)
			{
				if (Logging::GetCoreLogger())
					XCORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, instrumentorCurrentSession->name);
				InternalEndSession();
			}
			instrumentorOutputStream.open(filepath);
			if (instrumentorOutputStream.is_open())
			{
				instrumentorCurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else
				if (Logging::GetCoreLogger())
					XCORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
		}
		void EndSession()
		{
			std::lock_guard lock(instrumentorMutex);
			InternalEndSession();
		}
		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;
			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');
			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.elapsedTime.count()) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.threadID << ",";
			json << "\"ts\":" << result.start.count();
			json << "}";
			std::lock_guard lock(instrumentorMutex);
			if (instrumentorCurrentSession)
			{
				instrumentorOutputStream << json.str();
				instrumentorOutputStream.flush();
			}
		}
		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		void WriteHeader()
		{
			instrumentorOutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			instrumentorOutputStream.flush();
		}
		void WriteFooter()
		{
			instrumentorOutputStream << "]}";
			instrumentorOutputStream.flush();
		}
		void InternalEndSession()
		{
			if (instrumentorCurrentSession)
			{
				WriteFooter();
				instrumentorOutputStream.close();
				delete instrumentorCurrentSession;
				instrumentorCurrentSession = nullptr;
			}
		}
	private:
		std::mutex instrumentorMutex;
		InstrumentationSession* instrumentorCurrentSession;
		std::ofstream instrumentorOutputStream;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name) : timerName(name), timerStopped(false)
			{ timerStartTimepoint = std::chrono::steady_clock::now(); }
		~InstrumentationTimer()
		{
			if (!timerStopped)
				Stop();
		}
		void Stop()
		{
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ timerStartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(timerStartTimepoint).time_since_epoch();
			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ timerName, highResStart, elapsedTime, std::this_thread::get_id() });
			timerStopped = true;
		}
	private:
		const char* timerName;
		std::chrono::time_point<std::chrono::steady_clock> timerStartTimepoint;
		bool timerStopped;
	};
}
#define XPROFILE 1
#if XPROFILE
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define X_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define X_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
		#define X_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define X_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define X_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define X_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define X_FUNC_SIG __func__
	#else
		#define X_FUNC_SIG "X_FUNC_SIG unknown!"
	#endif
	#define XPROFILE_BEGIN_SESSION(name, filepath) ::XEngine::Instrumentor::Get().BeginSession(name, filepath)
	#define XPROFILE_END_SESSION() ::XEngine::Instrumentor::Get().EndSession()
	#define XPROFILE_SCOPE(name) ::XEngine::InstrumentationTimer timer##__LINE__(name);
	#define XPROFILE_FUNCTION() XPROFILE_SCOPE(X_FUNC_SIG)
#else
	#define XPROFILE_BEGIN_SESSION(name, filepath)
	#define XPROFILE_END_SESSION()
	#define XPROFILE_SCOPE(name)
	#define XPROFILE_FUNCTION()
#endif