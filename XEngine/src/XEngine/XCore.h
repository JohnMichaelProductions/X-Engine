#pragma once
#ifdef X_PLATFORM_WINDOWS																							// IF THE COMPUTERS PLATFORM IS WINDOWS
#if X_DYNAMIC_LINK																									// IF X-ENGINE IS DYNAMICALLY LINKED
	#ifdef X_BUILD_DLL																									// IF X-ENGINE IS BUILT AS A DLL
		#define XENGINE_API __declspec(dllexport)																			// EXPORT DLL SYMBOLS
	#else																												// IF X-ENGINE IS NOT BUILT AS A DLL
		#define XENGINE_API __declspec(dllimport)																			// IMPORT DLL SYMBOLS
	#endif																											// END IF
#else																												// IF X-ENGINE IS NOT DYNAMICALLY LINKED
	#define XENGINE_API																									// DEFINE XENGINE_API
#endif																												// END IF
#else																												// IF THE COMPUTERS PLATFORM IS NOT WINDOWS
	#error X-Engine only supports Windows 64-bit
#endif																												// END IF
#ifdef X_DEBUG																										// IF X-ENGINE IS SET TO DEBUG
	#define X_ENABLE_ASSERTS																							// ENABLE ASSERTS
#endif																												// END IF
#ifdef X_ENABLE_ASSERTS																								// IF ASSERTS ARE ENABLED
	#define X_ASSERT(x, ...) {if(!(x)) {XCLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }		// DEFINE ASSERT
	#define XCORE_ASSERT(x, ...)  {if(!(x)) {XCORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }		// DEFINE ASSERT
#else																												// IF ASSETS ISN'T ENABLED
	#define X_ASSERT(x, ...)																							// DEFINE ASSERT AS NULL
	#define XCORE_ASSERT(x, ...)																						// DEFINE ASSERT AS NULL
#endif																												// END IF
#define BIT(x) (1 << x)																								// Macro: Bit Macro
#define X_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)												// Macro: Binding Macro
