#include "Xpch.h"
#include <GLM/glm.hpp>
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Components.h"
#include "XEngine/Renderer/RendererAPI/Renderer2D.h"
namespace XEngine
{
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	}
	Scene::~Scene() {}
	entt::entity Scene::CreateEntity()
		{ return m_Registry.create(); }
	void Scene::OnUpdate(Timestep timestep)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}