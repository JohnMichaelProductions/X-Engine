#pragma once
// Platform support
#ifdef X_PLATFORM_WINDOWS
	#ifdef X_BUILD_DLL
		#define XENGINE_API __declspec(dllexport)
	#else
		#define XENGINE_API __declspec(dllimport)
	#endif
#else
	#error X-Engine only supports Windows 64-bit
#endif
#ifdef X_ENABLE_ASSERTS
	#define X_ASSERT(x, ...) {if(!(x)) {X_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define X_CORE_ASSERT(x, ...)  {if(!(x)) {X_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define X_ASSERT(x, ...)
	#define X_CORE_ASSERT(x, ...)
#endif
// Bit for Event System
#define BIT(x) (1 << x)