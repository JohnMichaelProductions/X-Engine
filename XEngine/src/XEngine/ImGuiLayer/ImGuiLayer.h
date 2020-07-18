#pragma once
#include "XEngine/LayerSystem/Layer.h"
#include "XEngine/EventSystem/KeyEvent.h"
#include "XEngine/EventSystem/MouseEvent.h"
#include "XEngine/EventSystem/ApplicationEvent.h"
namespace XEngine
{
	class XENGINE_API ImGuiLayer : public Layer
	{
	public:
		// Defined in Source File
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float mainTime = 0.0f;
	};
}