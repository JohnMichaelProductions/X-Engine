// Input Class
#pragma once
#include "XEngine/Core/XCore.h"
namespace XEngine
{
	class XENGINE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) 
			{ return inputInstance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) 
			{ return inputInstance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePostion() 
			{ return inputInstance->GetMousePositionImpl(); }
		inline static float GetMouseX() 
			{ return inputInstance->GetMouseXImpl(); }
		inline static float GetMouseY() 
			{ return inputInstance->GetMouseYImpl(); }
	private:
		static Scope<Input> inputInstance;
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	};
}