#include <ImGui/imgui.h>
#include "Panels/Hierarchy.h"
#include "XEngine/Scene/Components.h"
namespace XEngine
{
	Hierarchy::Hierarchy(const Ref<Scene>& context)
		{ SetContext(context); }
	void Hierarchy::SetContext(const Ref<Scene>& context)
		{ m_Context = context; }
	void Hierarchy::OnImGuiRender()
	{
		ImGui::Begin("Hierarchy");
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity { entityID, m_Context.get() };
			DrawEntityNode(entity);
		});
		ImGui::End();
	}
	void Hierarchy::DrawEntityNode(Entity entity)
	{
		if (!entity.HasComponent<TagComponent>())
			entity.AddComponent<TagComponent>();
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
			m_SelectionContext = entity;
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)465454, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}
}