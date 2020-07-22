#pragma once
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
namespace XEngine
{
	struct ProfileResult
	{
		std::string name;
		long long start, end;
		uint32_t threadID;
	};
	struct InstrumentationSession
		{ std::string name; };
	class Instrumentor
	{
	public:
		Instrumentor() : instrumentorCurrentSession(nullptr), instrumentorProfileCount(0) {}
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			instrumentorOutputStream.open(filepath);
			WriteHeader();
			instrumentorCurrentSession = new InstrumentationSession{ name };
		}
		void EndSession()
		{
			WriteFooter();
			instrumentorOutputStream.close();
			delete instrumentorCurrentSession;
			instrumentorCurrentSession = nullptr;
			instrumentorProfileCount = 0;
		}
		void WriteProfile(const ProfileResult& result)
		{
			if (instrumentorProfileCount++ > 0)
				instrumentorOutputStream << ",";
			std::string name = result.name;
			std::replace(name.begin(), name.end(), '"', '\'');
			instrumentorOutputStream << "{";
			instrumentorOutputStream << "\"cat\":\"function\",";
			instrumentorOutputStream << "\"dur\":" << (result.end - result.start) << ',';
			instrumentorOutputStream << "\"name\":\"" << name << "\",";
			instrumentorOutputStream << "\"ph\":\"X\",";
			instrumentorOutputStream << "\"pid\":0,";
			instrumentorOutputStream << "\"tid\":" << result.threadID << ",";
			instrumentorOutputStream << "\"ts\":" << result.start;
			instrumentorOutputStream << "}";
			instrumentorOutputStream.flush();
		}
		void WriteHeader()
		{
			instrumentorOutputStream << "{\"otherData\": {},\"traceEvents\":[";
			instrumentorOutputStream.flush();
		}
		void WriteFooter()
		{
			instrumentorOutputStream << "]}";
			instrumentorOutputStream.flush();
		}
		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private:
		InstrumentationSession* instrumentorCurrentSession;
		std::ofstream instrumentorOutputStream;
		int instrumentorProfileCount;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name) : timerName(name), timerStopped(false)
			{ timerStartTimepoint = std::chrono::high_resolution_clock::now(); }
		~InstrumentationTimer()
		{
			if (!timerStopped)
				Stop();
		}
		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(timerStartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ timerName, start, end, threadID });
			timerStopped = true;
		}
	private:
		const char* timerName;
		std::chrono::time_point<std::chrono::high_resolution_clock> timerStartTimepoint;
		bool timerStopped;
	};
}
#define XPROFILE 1
#if XPROFILE
	#define XPROFILE_BEGIN_SESSION(name, filepath) ::XEngine::Instrumentor::Get().BeginSession(name, filepath)
	#define XPROFILE_END_SESSION() ::XEngine::Instrumentor::Get().EndSession()
	#define XPROFILE_SCOPE(name) ::XEngine::InstrumentationTimer timer##__LINE__(name);
	#define XPROFILE_FUNCTION() XPROFILE_SCOPE(__FUNCSIG__)
#else
	#define XPROFILE_BEGIN_SESSION(name, filepath)
	#define XPROFILE_END_SESSION()
	#define XPROFILE_SCOPE(name)
	#define XPROFILE_FUNCTION()
#endif