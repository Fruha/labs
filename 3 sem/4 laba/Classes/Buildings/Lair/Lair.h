#pragma once
#include "Abstract/GameObject.h"
#include "Enemy.h"
#include "cocos2d.h"
#include "GameInfo.h"

namespace game
{
	class Field;
	class cocos2d::FiniteTimeAction;
	class Lair : public GameObject
	{
	private:
		void backWay(Point tile, Point previousStep, Field* field, std::vector < std::vector <int> >& pathLen, cocos2d::Vector<FiniteTimeAction*>& tempWay);
		void minWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen);
		void findWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen);
		FiniteTimeAction* createWayOneTile(Point start, Point end, Point tile, Field* field);
		double speed = 0.5;
		double height = 15;

	protected:
	public:
		double rate = 4;
		Sequence* way = nullptr;
		Sequence* wayWithDamage = nullptr;
		std::list<Enemy*> enemies;

		Lair(std::string t_path, Point t_position, Point t_scale = { 1,1 });
		void createWay(Field* field);
		void addEnemy(MainScene* hw, Field* field, int t_life);

	};
}