#pragma once
#include "XCore.h"
namespace XEngine 
{
	class XENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	Application* CreateApplication();
}

