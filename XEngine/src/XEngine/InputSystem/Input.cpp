#include "Xpch.h"
#include "XEngine/InputSystem/Input.h"
#ifdef X_PLATFORM_WINDOWS
	#include "Platforms/OperatingSystems/Windows10/Win10Input.h"
#endif
namespace XEngine
{
	Scope<Input> Input::inputInstance = Input::Create();
	Scope<Input> Input::Create()
	{
		#ifdef X_PLATFORM_WINDOWS
			return CreateScope<Win10Input>();
		#else
			XCORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}