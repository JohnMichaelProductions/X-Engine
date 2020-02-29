#pragma once
#pragma region INCLUDE / NAMESPACES
#include "XCore.h"
#pragma endregion
namespace XEngine
{
	#pragma region APPLICATION CLASS
	class XENGINE_API Application
	{
	public:
		// Creates functions
		Application();
		virtual ~Application();
		void Run();
	};
	#pragma endregion
	Application* CreateApplication();
}

