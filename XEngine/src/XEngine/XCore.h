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
// Bit for Event System
#define BIT(x) (1 << x)