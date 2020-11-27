#pragma once
#include <string>
#include "Abstract/ClickableObject.h"
#include "Abstract/GameObject.h"
#include "cocos2d.h"
#include "Buildings/Tower/Tower.h"
#include "Buildings/Castle/Castle.h"
#include "Buildings/Lair/Lair.h"
#include "Buildings/Trap/Trap.h"

namespace game 
{
	class Tile : public ClickableObject
	{
	private:
	protected:
	public:
		enum State { CANT_BUILD, CAN_BUILD_TOWER, CANT_BUILD_TOWER, CAN_BUILD_TRAP, CANT_BUILD_TRAP};

		State state = CANT_BUILD;
		bool isRoad = 0;
		Tower* tower = nullptr;
		Trap* trap = nullptr;
		Castle* castle = nullptr;
		Lair* lair = nullptr;

		Tile() :
			ClickableObject()
		{};
		Tile(std::string t_path, Point t_position, std::vector<Point> ClickPoligon_t, Point t_scale) :
			ClickableObject(t_path, t_position, ClickPoligon_t, t_scale)
		{};

		void buildTower(MainScene* hw, Tower::Type type);
		void buildTrap(MainScene* hw, Trap::Type type);

		void destroyBuilding(MainScene* hw);

		void buildCastle(MainScene* hw, int life, int gold);
		void buildLair(MainScene* hw);
	};
}
