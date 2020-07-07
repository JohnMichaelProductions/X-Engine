// Header file for Time class
#pragma once
namespace XEngine
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : deltaTime(time) {}
		operator float()
			{ return deltaTime; }
		float GetSeconds() const
			{ return deltaTime; }
		float GetMilliseconds() const 
			{ return deltaTime * 1000.0f; }
	private:
		float deltaTime;
	};
}