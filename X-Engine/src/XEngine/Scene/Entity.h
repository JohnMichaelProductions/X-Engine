#pragma once
#include <entt.hpp>
#include "XEngine/Scene/Scene.h"
namespace XEngine
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;
		// Add Component
		template<typename Component, typename... Args>
		Component& AddComponent(Args&&... args)
		{
			XCORE_ASSERT(!HasComponent<Component>(), "Entity already has component");
			return m_Scene->m_Registry.emplace<Component>(m_EntityHandle, std::forward<Args>(args)...);
		}
		// Get Component
		template<typename Component>
		Component& GetComponent()
		{
			XCORE_ASSERT(HasComponent<Component>(), "Entity does not component");
			return m_Scene->m_Registry.get<Component>(m_EntityHandle);
		}
		// Remove Component
		template<typename Component>
		void RemoveComponent()
		{
			XCORE_ASSERT(HasComponent<Component>(), "Entity does not component");
			m_Scene->m_Registry.remove<Component>(m_EntityHandle);
		}
		// Has Component
		template<typename Component>
		bool HasComponent()
			{ return m_Scene->m_Registry.has<Component>(m_EntityHandle); }
		operator bool() const
			{ return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}