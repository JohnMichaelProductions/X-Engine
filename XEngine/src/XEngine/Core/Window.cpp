#include "Xpch.h"
#include "XEngine/Core/Window.h"
#ifdef X_PLATFORM_WINDOWS
	#include "Platforms/OperatingSystems/Windows10/Win10Window.h"
#endif
namespace XEngine
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef X_PLATFORM_WINDOWS
			return CreateScope<Win10Window>(props);
		#else
			XCORE_ASSERT(false, "Unknown Platform");
			return nullptr;
		#endif
	}
}