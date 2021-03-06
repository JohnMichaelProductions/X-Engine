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
		void OnImGuiRender();
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		// Members
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		// Friends
		friend class Entity;
		friend class Hierarchy;
	};
}