#include "Xpch.h"
#include <GLM/glm.hpp>
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Entity.h"
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
	Entity Scene::CreateEntity(const std::string tagName)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = tagName.empty() ? "Entity" : tagName;
		return entity;
	}
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