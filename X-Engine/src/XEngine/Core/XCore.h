// X-Engine Core File
#pragma once
#include <memory>
// Platforms
#ifdef _WIN32
	#ifdef _WIN64
		#define XPLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define X_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define X_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define XPLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define XPLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif
// Configurations
#ifdef XDEBUG
	#if defined(XPLATFORM_WINDOWS)
		#define XDEBUGBREAK() __debugbreak()
	#elif defined(X_PLATFORM_LINUX)
		#include <signal.h>
		#define XDEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define  XENABLE_ASSERTS
#else
	#define XDEBUGBREAK()
#endif
#ifdef XENABLE_ASSERTS
	#define X_ASSERT(x, ...) {if(!(x)) {XCLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); XDEBUGBREAK(); } }
	#define XCORE_ASSERT(x, ...)  {if(!(x)) {XCORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); XDEBUGBREAK(); } }
#else
	#define XASSERT(x, ...)
	#define XCORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)
#define XBIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
namespace XEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
		{ return std::make_unique<T>(std::forward<Args>(args)...); }
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
		{ return std::make_shared<T>(std::forward<Args>(args)...); }
}