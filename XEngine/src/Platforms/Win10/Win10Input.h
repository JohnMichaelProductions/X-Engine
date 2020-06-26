// Header file that deals with input on window 10 computers
#pragma once
#include "XEngine/InputSystem/Input.h"
namespace XEngine
{
	class Win10Input : public Input
	{
	protected:
		// Defined in Source File
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}