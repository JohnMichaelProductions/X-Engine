// Input Class
#pragma once
#include "XEngine/Core/XCore.h"
#include "XEngine/InputSystem/XEngineInputCodes.h"
#include "XEngine/InputSystem/XEngineMouseCodes.h"
namespace XEngine
{
	class Input
	{
	public:
		inline static bool IsKeyPressed(KeyCode key)
			{ return inputInstance->IsKeyPressedImpl(key); }
		inline static bool IsMouseButtonPressed(MouseCode button)
			{ return inputInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePostion()
			{ return inputInstance->GetMousePositionImpl(); }
		inline static float GetMouseX()
			{ return inputInstance->GetMouseXImpl(); }
		inline static float GetMouseY()
			{ return inputInstance->GetMouseYImpl(); }
		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> inputInstance;
	};
}