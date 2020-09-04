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
		// Methods
		//void CommenceDraw(const char* name, void* valueAddress, size_t& hashcode);
		void DrawProperties(Entity& entity);
	};
}