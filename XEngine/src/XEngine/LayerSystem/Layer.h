#pragma once
#include "XEngine/XCore.h"
#include "XEngine/EventSystem/Event.h"
namespace XEngine
{
	class XENGINE_API Layer
	{
	public:											// {PUBLIC}
		Layer(const std::string& name = "Layer");	// Constructor Function: Called opon creation
		virtual ~Layer();							// (Virtual) Destructor Function: Called when object is deleted
		virtual void OnAttach() {}					// (Virtual) On Attach Function: Called when the layer is attached
		virtual void OnDetach() {}					// (Virtual) On Detach Function: Called when the layer is detached
		virtual void OnUpdate() {}					// (Virtual) On Update Function: Called every frame
		virtual void OnImGuiRender() {}				// (Virtual) On ImGui Render Function: Called when ImGui is rendered
		virtual void OnEvent(Event& event) {}		// (Virtual) On Event Function: Called when an event happens in the layer
		inline const std::string& GetName() const	// Get Name Function: Returns layer name
			{ return memberDebugName; }
	protected:										// {PROTECTED}
		std::string memberDebugName;				// Layer Name, to be specified when creating new layer
	};
}