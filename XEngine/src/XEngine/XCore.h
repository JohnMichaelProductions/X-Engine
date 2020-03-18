#pragma once
// Platform Support
#ifdef X_PLATFORM_WINDOWS
#if X_DYNAMIC_LINK
	#ifdef X_BUILD_DLL
		#define XENGINE_API __declspec(dllexport)
	#else
		#define XENGINE_API __declspec(dllimport)
	#endif
#else
	#define XENGINE_API
#endif
#else
	#error X-Engine only supports Windows 64-bit
#endif
#ifdef X_DEBUG
	#define X_ENABLE_ASSERTS
#endif
#ifdef X_ENABLE_ASSERTS
	// If x is equal to false(or 0) then execute following code
	#define X_ASSERT(x, ...) {if(!(x)) {XCLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define XCORE_ASSERT(x, ...)  {if(!(x)) {XCORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define X_ASSERT(x, ...)
	#define X_CORE_ASSERT(x, ...)
#endif
// Macro Bit for Event System
#define BIT(x) (1 << x)
// Macro for dispacting events
#define X_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 
