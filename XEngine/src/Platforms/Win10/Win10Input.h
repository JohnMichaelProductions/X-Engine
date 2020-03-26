#pragma once
#include "XEngine/InputSystem/Input.h"
namespace XEngine
{
	class Win10Input : public Input
	{
	protected:																// {PROTECTED}
		virtual bool IsKeyPressedImpl(int keycode) override;				// (Virtual) (Override) Is Key Pressed Implementation:
		virtual bool IsMouseButtonPressedImpl(int button) override;			// (Virtual) (Override) Is Mouse Button Pressed Implementation:
		virtual std::pair<float, float> GetMousePositionImpl() override;	// (Virtual) (Override) Get Mouse Position Implementation:
		virtual float GetMouseXImpl() override;								// (Virtual) (Override) Get Mouse X Implementation:
		virtual float GetMouseYImpl() override;								// (Virtual) (Override) Get Mouse YImplementation:
	};
}