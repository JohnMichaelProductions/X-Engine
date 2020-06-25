// Layer class header file
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
		virtual void OnAttach() 
			{ XCORE_INFO("{0} attached", GetName()); }
		virtual void OnDetach() 
			{ XCORE_INFO("{0} detached", GetName()); }
		virtual void OnUpdate() 
		{
			if(layerUpdates)
				XCORE_ERROR("{0} Updated", GetName());
		}
		virtual void OnImGuiRender() = 0;
		virtual void OnEvent(Event& event) 
			{ XCORE_TRACE("{0}", event.GetName()); }
		inline const std::string& GetName() const
			{ return layerDebugName; }
		bool layerUpdates;
	protected:
		std::string layerDebugName;
	};
}