#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Entity.h"
namespace XEngine
{
	class Hierarchy
	{
	public:
		Hierarchy() = default;
		Hierarchy(const Ref<Scene>& context);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();
	private:
		// Methods
		void DrawEntityNode(Entity entity);
		// Members
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}