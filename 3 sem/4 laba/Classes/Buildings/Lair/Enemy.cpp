#include "Enemy.h"
#include "Lair.h"
#include <algorithm>
#include "MainScene.h"
#include "Tiles/Field.h"
#include "Buildings/Castle/Castle.h"
#include "Effect/Effect.h"

namespace game 
{
	void Enemy::getDamage(MainScene* hw, float damage) 
	{
		if (lifeObject == nullptr)
		{
			return;
		}
		life = std::max(life - damage, 0.f);
		std::string temp = std::to_string(life);
		lifeObject->label->setString(temp.substr(0, temp.size() - 4));
		if (life <= 0.001)
		{
			hideAll(hw);
			Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
			castle->changeGold(getGold());
			Lair* lair = hw->field_level1->tiles[(int)hw->field_level1->start_enemy.x][(int)hw->field_level1->start_enemy.y].lair;
			lair->enemies.remove(this);
		}
	}

	void Enemy::addEffect(MainScene* hw, Effect effect)
	{
		effects.push_back(new Effect(effect));
	}

	void Enemy::updateEffects(MainScene* hw, float dt)
	{
		std::list<Effect*>::iterator it;
		for (it = effects.begin(); it != effects.end() ; it++)
		{
			if ((*it)->type == (*it)->POISONING && life >= 0)
			{
				this->getDamage(hw, std::min(dt, (*it)->timeLeft) * (*it)->power);
			}
			(*it)->timeLeft -= dt;
			if ((*it)->timeLeft <= 0) 
			{
				delete(*it);
				(*it) = nullptr;
			}
		}
		effects.remove(nullptr);
	}

	void Enemy::moveAllPath() 
	{
		sprite->runAction(wayWithDamage->clone());
		lifeObject->label->runAction(way->clone());
	}
	void Enemy::showAll(MainScene* hw, int showLevel)
	{
		this->show(hw, 1);
		std::string temp = std::to_string(life);
		lifeObject->label->setString(temp.substr(0, temp.size() - 4));
		lifeObject->show(hw, 1);
	}
	void Enemy::hideAll(MainScene* hw)
	{
		this->hide(hw);
		lifeObject->hide(hw);
		delete(lifeObject);
		lifeObject = nullptr;
	}

	int Enemy::getGold()
	{
		return ((int)std::pow(maxLife / 5, 3.f/4.f));
	}
}