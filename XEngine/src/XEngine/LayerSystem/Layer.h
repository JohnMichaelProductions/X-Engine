#pragma once
#include "XEngine/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class XENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const
			{ return memberDebugName; }
	protected:
		std::string memberDebugName;
	};
}