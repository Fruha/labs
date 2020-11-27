#pragma once
#include "Abstract/GameObject.h"
#include "Abstract/ClickableObject.h"
#include "Tiles/Tile.h"

namespace game
{
	class MenuObject : public GameObject
	{
	private:
	protected:
	public:
		enum Type { MENU_SHOP_TOWERS, MENU_TOWER, MENU_SHOP_TRAPS, MENU_TRAP };

		Type type;
		std::vector<ClickableObject> menuSelections;
		std::vector<GameObject> objects;
		std::vector<GameObject> stats;
		std::vector<int> prices;

		MenuObject(MainScene* hw, Point t_position, Type t_type);

		void show(MainScene* hw);
		void hide(MainScene* hw);
		std::vector<std::function<void(MainScene*, game::Tile&)>> action;
	};
}