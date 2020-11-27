#pragma once

namespace game 
{
	class Effect 
	{
	private:
	protected:
	public:
		enum Type { POISONING, WEAKNESS };
		
		Type type;
		float timeLeft;
		float power;

		Effect(Type t_type, float t_timeLeft, float t_power) :
			type(t_type),
			timeLeft(t_timeLeft),
			power(t_power)
		{};
	};
}