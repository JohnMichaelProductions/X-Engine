#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/Scene/Scene.h"
namespace XEngine
{
	class Properties
	{
	public:
		Properties() = default;
		void OnImGuiRender(Entity& entity);
	private:
		void DrawProperties(Entity& entity);
	};
}