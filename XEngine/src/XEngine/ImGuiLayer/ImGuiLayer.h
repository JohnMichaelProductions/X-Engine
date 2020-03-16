#pragma once
// Event System Files
#include "XEngine/EventSystem/ApplicationEvent.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
// Layer System Files
#include "XEngine/LayerSystem/Layer.h"
namespace XEngine
{
	class XENGINE_API ImGuiLayer : public Layer
	{
	public:
		// ---FUNCTIONS---
		ImGuiLayer();
		~ImGuiLayer();
			// ---Override Functions from Layer Class---
			virtual void OnAttach() override;
			virtual void OnDetach() override;
			virtual void OnImGuiRender() override;
			// -----------------------------------------
		void Begin();
		void End();
		// ---------------
	private:
		// Time Variable
		float mainTime = 0.0f;
	};
}

