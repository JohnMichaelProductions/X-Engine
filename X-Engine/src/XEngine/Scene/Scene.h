#pragma once
#include "XEngine/Core/Time.h"
#include "../../../vendor/Entt/include/entt.hpp"
namespace XEngine
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		entt::entity CreateEntity();
		void OnUpdate(Timestep timestep);
		// TEMP
		entt::registry& Reg() { return m_Registry; }
	private:
		entt::registry m_Registry;
	};
}