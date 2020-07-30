// Layer class header file
#pragma once
#include "XEngine/Core/Time.h"
#include "XEngine/Core/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class Layer
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
		virtual void OnUpdate(Timestep timestep) { }
		virtual void OnEvent(Event& event) 
			{ /* XCORE_TRACE("{0}", event.GetName()); */}
		const std::string& GetName() const
			{ return layerDebugName; }
	protected:
		std::string layerDebugName;
	};
}