// Layer class header file
#pragma once
#include "XEngine/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class XENGINE_API Layer
	{
	public:
		// Defined in Source File
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnImGuiRender() = 0;
		// Prototype in Header File
		virtual void OnAttach() 
			{ XCORE_INFO("{0} attached", GetName()); }
		virtual void OnDetach() 
			{ XCORE_INFO("{0} detached", GetName()); }
		virtual void OnUpdate() 
		{
			if(layerUpdates)
				XCORE_ERROR("{0} Updated", GetName());
		}
		virtual void OnEvent(Event& event) 
		{
			if(layerUpdates)
				XCORE_TRACE("{0}", event.GetName()); 
		}
		inline const std::string& GetName() const
			{ return layerDebugName; }
	protected:
		std::string layerDebugName;
		bool layerUpdates;
	};
}