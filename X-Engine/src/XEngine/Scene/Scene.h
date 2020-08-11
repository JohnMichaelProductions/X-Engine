#pragma once
#include <entt.hpp>
#include "XEngine/Core/Time.h"
namespace XEngine
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string tagName = std::string());
		void OnUpdate(Timestep timestep);
	private:
		entt::registry m_Registry;
		friend class Entity;
	};
}