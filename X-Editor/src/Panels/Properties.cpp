#include <ImGui/imgui.h>
#include "Panels/Properties.h"
#include <glm/gtc/type_ptr.hpp>
#include "XEngine/Scene/Components.h"
namespace XEngine
{
	void Properties::OnImGuiRender(Entity& entity)
	{
		ImGui::Begin("Properties");
		if(entity)
			DrawProperties(entity);
		ImGui::End();
	}
	void Properties::DrawProperties(Entity& entity)
	{
		// Tag
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>();
			char* cstr = new char[tag.Tag.length() + 1];
			strcpy(cstr, tag.Tag.c_str());
			ImGui::InputText("Name", cstr, 64, ImGuiInputTextFlags_None, NULL, NULL);
			delete[] cstr;
		}
		// Transform
		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>();
			ImGui::Separator();
			ImGui::Text("Transform Component");
			ImGui::DragFloat3("Position", glm::value_ptr(transform.Position), 0.1f);
			ImGui::DragFloat("Rotation", &transform.Rotation, 0.1f);
			ImGui::DragFloat2("Size", glm::value_ptr(transform.Size), 0.1f);
		}
		// Camera
		if (entity.HasComponent<CameraComponent>())
		{
			auto& camera = entity.GetComponent<CameraComponent>();
			ImGui::Separator();
			ImGui::Text("Camera Component");
			ImGui::Checkbox("Primary Camera", &camera.Primary);
			ImGui::Checkbox("Fixed Aspect Ratio", &camera.FixedAspectRatio);
		}
		// Sprite Renderer
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			auto& sprite = entity.GetComponent<SpriteRendererComponent>();
			ImGui::Separator();
			ImGui::Text("Sprite Renderer Component");
			ImGui::ColorEdit4("Color", glm::value_ptr(sprite.Color), 0.1f);
			// TODO: Add Texture
			ImGui::DragFloat("Tilling Factor", &sprite.TillingFactor, 0.1f);
		}
	}
}