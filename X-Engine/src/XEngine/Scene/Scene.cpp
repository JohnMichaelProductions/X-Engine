#include "Xpch.h"
#include <GLM/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XEngine/Scene/Scene.h"
#include "XEngine/Scene/Entity.h"
#include "XEngine/Scene/Components.h"
#include "XEngine/Renderer/RendererAPI/Renderer2D.h"
// TODO: Fix path to <ImGui/imgui.h>
#include "../../../vendor/ImGui/imgui.h"
namespace XEngine
{
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity, glm::vec3(1.0f), glm::vec2(1.0f), 0.0f);
	}
	Scene::~Scene() {}
	Entity Scene::CreateEntity(const std::string tagName)
	{
		Entity entity = { m_Registry.create(), this };
		// All entities start with a transform and tag component
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = tagName.empty() ? "Entity" : tagName;
		return entity;
	}
	void Scene::OnUpdate(Timestep timestep)
	{
		// Updating Scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			// TODO: Move to Scene::OnScenePlay
			if (!nsc.Instance)
			{
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_Entity = Entity{ entity, this };
				nsc.Instance->OnCreate();
			}
			nsc.Instance->OnUpdate(timestep);
		});
		// Render 2D
		Camera* primaryCamera = nullptr;
		glm::mat4* cameraTransform = nullptr;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				primaryCamera = &camera.Camera;
				cameraTransform = &transform.CalculateMatrix();
				break;
			}
		}
		if (primaryCamera)
		{
			Renderer2D::BeginScene(primaryCamera->GetProjection(), *cameraTransform);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				if (sprite.Texture == nullptr)
					Renderer2D::DrawRotatedQuad(transform.Position, transform.Size, transform.Rotation, sprite.Color);
				else
					Renderer2D::DrawRotatedQuad(transform.Position, transform.Size, transform.Rotation, sprite.Texture, sprite.TillingFactor, sprite.Color);
			}
			Renderer2D::EndScene();
		}
	}
	void Scene::OnImGuiRender() {}
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}
}