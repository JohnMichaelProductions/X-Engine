#pragma once
// Mid Files
#include "XEngine/XCore.h"
// Event System Files
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class XENGINE_API Layer
	{
	public:
		// Layer takes in a name
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		// Called when a layer is attached
		virtual void OnAttach() {}
		// Called when a layer is detached
		virtual void OnDetach() {}
		// Called when the a layer is update(every frame)
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		// Called when an a event is sent to a layer
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		// Debug string
		std::string m_DebugName;
	};
}