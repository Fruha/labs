#pragma once
#include "Abstract/GameObject.h"
#include "Effect/Effect.h"

namespace game 
{
	class Enemy : public GameObject 
	{
	private:
		float life;
		float maxLife;
	protected:
	public:
		std::list<Effect*> effects = {};
		Sequence* way = nullptr;
		Sequence* wayWithDamage = nullptr;
		GameObject* lifeObject = nullptr;

		Enemy(std::string t_text, Point t_position, Sequence* t_way, Sequence* t_wayWithDamage, float t_life, Point t_scale = { 1,1 }) :
			GameObject(t_text, t_position, t_scale),
			way(t_way),
			wayWithDamage(t_wayWithDamage),
			life(t_life),
			maxLife(t_life),
			lifeObject(new GameObject(std::to_string(t_life), t_position, 20))
		{
			lifeObject->label->enableOutline(Color4B::BLACK, 2);
		};
		void getDamage(MainScene* hw, float damage);
		void addEffect(MainScene* hw, Effect effect);
		void updateEffects(MainScene* hw, float dt);
		void showAll(MainScene* hw, int showLevel);
		void hideAll(MainScene* hw);
		void moveAllPath();
		int getGold();

	};
}