#include <ImGui/imgui.h>
#include "Panels/Properties.h"
#include <glm/gtc/type_ptr.hpp>
#include "XEngine/Scene/DataTypes.h"
#include "XEngine/Scene/Components.h"
#include <Visit_Struct/include/visit_struct/visit_struct.hpp>
namespace XEngine
{
	static struct PropertyArtist
	{
		template <typename GenericType>
		void operator()(const char* name, GenericType& value)
		{
			size_t hashcode = typeid(value).hash_code();
			void* valueAddress = &value;
			CommenceDraw(name, valueAddress, hashcode);
		}
		void CommenceDraw(const char* name, void* valueAddress, size_t& hashcode)
		{
			// Int
			if (hashcode == typeid(int).hash_code())
			{
				int* value = static_cast<int*>(valueAddress);
				ImGui::DragInt(name, value);
			}
			// Float
			else if (hashcode == typeid(float).hash_code())
			{
				float* value = static_cast<float*>(valueAddress);
				ImGui::DragFloat(name, value);
			}
			// Bool
			else if (hashcode == typeid(bool).hash_code())
			{
				bool* valuePtr = static_cast<bool*>(valueAddress);
				ImGui::Checkbox(name, valuePtr);
			}
			// String
			else if (hashcode == typeid(std::string).hash_code())
			{
				std::string* valuePtr = static_cast<std::string*>(valueAddress);
				std::string value = *valuePtr;
				auto& tag = value;
				char* cstr = new char[tag.length() + 1];
				strcpy(cstr, tag.c_str());
				ImGui::InputText(name, cstr, 64, ImGuiInputTextFlags_None, NULL, NULL);
				delete[] cstr;
			}
			// XVec2
			else if (hashcode == typeid(glm::vec2).hash_code())
			{
				XVec2* valuePtr = static_cast<XVec2*>(valueAddress);
				glm::vec2 value = *valuePtr;
				ImGui::DragFloat2(name, glm::value_ptr(value), 0.1f);
			}
			// XVec3
			else if (hashcode == typeid(glm::vec3).hash_code())
			{
				glm::vec3* valuePtr = static_cast<glm::vec3*>(valueAddress);
				glm::vec3 value = *valuePtr;
				ImGui::DragFloat3(name, glm::value_ptr(value), 0.1f);
			}
			// XVec4
			else if (hashcode == typeid(XVec4).hash_code())
			{
				XVec4* valuePtr = static_cast<XVec4*>(valueAddress);
				glm::vec4 value = *valuePtr;
				ImGui::DragFloat4(name, glm::value_ptr(value), 0.1f);
			}
			// XColor3
			else if (hashcode == typeid(XColor3).hash_code())
			{
				XVec3* valuePtr = static_cast<XVec3*>(valueAddress);
				glm::vec3 value = *valuePtr;
				ImGui::ColorEdit3(name, glm::value_ptr(value), 0.1f);
			}
			// XColor4
			else if (hashcode == typeid(XColor4).hash_code())
			{
				XVec4* valuePtr = static_cast<XVec4*>(valueAddress);
				glm::vec4 value = *valuePtr;
				ImGui::ColorEdit4(name, glm::value_ptr(value), 0.1f);
			}
		}
	};
	void Properties::OnImGuiRender(Entity& entity)
	{
		ImGui::Begin("Properties");
		if(entity)
			DrawProperties(entity);
		ImGui::End();
	}
	void Properties::DrawProperties(Entity& entity)
	{
		TransformComponent& component = entity.GetComponent<TransformComponent>();
		const char* name = component.ComponentName.c_str();
		ImGui::Text(entity.GetComponent<TagComponent>().Tag.c_str());
		ImGui::Separator();
		ImGui::Text(name);
		visit_struct::for_each(component, PropertyArtist{});
		ImGui::Separator();
	}
}