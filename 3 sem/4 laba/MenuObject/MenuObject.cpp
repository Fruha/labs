#include "MenuObject/MenuObject.h"
#include "Tiles/Tile.h"
#include "cocos2d.h"
#include "MainScene.h"
#include "Tiles/Field.h"
#include "MenuObject/MainMenu.h"
#include "GameInfo.h"

namespace game 
{
	MenuObject::MenuObject(MainScene* hw, Point t_position, Type t_type) :
		GameObject(t_position),
		type(t_type)
	{
		std::vector<std::vector<std::string>> allObjectsPaths = 
		{ 
			{
				"Isometric Tower defence pack/Sprites/Menu/Towers/redTower.png",
				"Isometric Tower defence pack/Sprites/Menu/Towers/purpleTower.png"
			}, 
			{
				"Isometric Tower defence pack/Sprites/Menu/MenuBuilding/levelUp.png",
				"Isometric Tower defence pack/Sprites/Menu/MenuBuilding/delete.png"
			},
			{
				"Isometric Tower defence pack/Sprites/Menu/Traps/poison.png"
			},
			{
				"Isometric Tower defence pack/Sprites/Menu/MenuBuilding/levelUp.png",
				"Isometric Tower defence pack/Sprites/Menu/MenuBuilding/delete.png"
			}
		};

		std::vector<std::vector<Point>> allObjectsScales =
		{
			{
				Point(0.15, 0.15),
				Point(0.15, 0.15)
			},
			{
				Point(0.08, 0.08),
				Point(0.15, 0.15)
			},
			{
				Point(0.12, 0.12)
			},
			{
				Point(0.08, 0.08),
				Point(0.15, 0.15)
			}
		};

		stats = std::vector<GameObject>();
		Tile& selectedTile = hw->field_level1->tiles[(int)hw->field_level1->selectedTile.x][(int)hw->field_level1->selectedTile.y];
		std::vector<std::vector<std::string>> names;
		switch (type)
		{
		case MENU_SHOP_TOWERS:
			prices = { CLASSIC_TOWER_PRICE_BUILD, MAGIC_TOWER_PRICE_BUILD };
			names =
			{
				{
					"Classic Tower",
					"Damage: " + std::to_string(CLASSIC_TOWER_START_DAMAGE),
					"Price: " + std::to_string(prices[0])
				},
				{
					"Magic Tower",
					"Damage: " + std::to_string(MAGIC_TOWER_START_DAMAGE),
					"Posion Damage: " + std::to_string(MAGIC_TOWER_EFFECT_POWER),
					"Duration: " + std::to_string(MAGIC_TOWER_EFFECT_TIMELEFT),
					"Price: " + std::to_string(prices[1])
				}
			};
			break;
		case MENU_TOWER:
			prices = { selectedTile.tower->getPriceLevelUp()};
			switch (selectedTile.tower->type)
			{
			case Tower::CLASSIC_TOWER:
				names =
				{
					{
						"LevelUp",
						"Dmg: " + std::to_string((int)selectedTile.tower->damage) + " upTo " + std::to_string((int)selectedTile.tower->damage + 1),
						"Price: " + std::to_string(prices[0])
					},
					{
						"Delete"
					}
				};
				break;
			case Tower::MAGIC_TOWER:
				names =
				{
					{
						"LevelUp",
						"Dmg: " + std::to_string((int)selectedTile.tower->damage) + " upTo " + std::to_string((int)selectedTile.tower->damage + 1),
						"Poison Dmg: " + std::to_string((int)selectedTile.tower->effect->power) + " upTo " + std::to_string((int)selectedTile.tower->effect->power + 1),
						"Duration: " + std::to_string((int)selectedTile.tower->effect->timeLeft) + " upTo " + std::to_string((int)selectedTile.tower->effect->timeLeft + 1),
						"Price: " + std::to_string(prices[0])
					},
					{
						"Delete"
					}
				};
				break;

			}
			break;
		case MENU_SHOP_TRAPS:
			prices = { POISON_TRAP_PRICE_BUILD };
			names =
			{
				{
					"Poison Trap",
					"Dmg: " + std::to_string(POISON_TRAP_START_DAMAGE),
					"Poison Dmg: " + std::to_string(POISON_TRAP_EFFECT_POWER),
					"Price: " + std::to_string(prices[0])
				}
			};
			break;
		case MENU_TRAP:
			prices = { selectedTile.trap->getPriceLevelUp() };
			names =
			{
				{
					"LevelUp",
					"Dmg: " + std::to_string((int)selectedTile.trap->damage) + " upTo " + std::to_string((int)selectedTile.trap->damage + 1),
					"Poison Dmg: " + std::to_string((int)selectedTile.trap->effect->power) + " upTo " + std::to_string((int)selectedTile.trap->effect->power + 1),
					"Duration: " + std::to_string((int)selectedTile.trap->effect->timeLeft) + " upTo " + std::to_string((int)selectedTile.trap->effect->timeLeft + 1),
					"Price: " + std::to_string(prices[0])
				},
				{
					"Delete"
				}
			};
			break;
		}

		int size = 0;
		for (int i1 = 0; i1 < names.size(); i1 += 1)
		{
			size += names[i1].size();
		}
		stats.resize(size);
		int sTemp = 0;
		for (int i1 = 0; i1 < names.size(); i1 += 1)
		{
			for (int i2 = 0; i2 < names[i1].size(); i2 += 1)
			{
				stats[sTemp] = GameObject(names[i1][i2], t_position + Point(-15, 350 - 220 * i1 + 40 - i2 * 30), 20);
				stats[sTemp].label->setAnchorPoint(Point(0, 0));
				sTemp += 1;
			}
		}
		switch (type) 
		{
		case MENU_SHOP_TOWERS:
			action =
			{
				([](MainScene* hw, Tile& tile)
					{
						int lessGold;
						Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
						if ((lessGold = hw->mainMenu->menu[hw->mainMenu->is_show_type]->prices[0]) <= castle->gold)
						{
							castle->changeGold(-lessGold);
							tile.buildTower(hw, Tower::CLASSIC_TOWER);
							tile.tower->showArea(hw, 1);
						}
					}
				),
				([](MainScene* hw, Tile& tile)
					{
						int lessGold;
						Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
						if ((lessGold = hw->mainMenu->menu[hw->mainMenu->is_show_type]->prices[1]) <= castle->gold)
						{
							castle->changeGold(-lessGold);
							tile.buildTower(hw, Tower::MAGIC_TOWER);
							tile.tower->showArea(hw, 1);
						}					
					}
				)
			};
			break;
		case MENU_TOWER:
			action =
			{
				[](MainScene* hw, Tile& tile)
				{
					int lessGold;
					Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
					if ((lessGold = tile.tower->getPriceLevelUp()) <= castle->gold)
					{
						castle->changeGold(-lessGold);
						tile.tower->levelUp();
					}
					
				},
				[](MainScene* hw, Tile& tile)
				{
					tile.destroyBuilding(hw);
				}
			};
			break;
		case MENU_SHOP_TRAPS:
			action =
			{
				[](MainScene* hw, Tile& tile)
				{
					int lessGold;
					Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
					if ((lessGold = hw->mainMenu->menu[hw->mainMenu->is_show_type]->prices[0]) <= castle->gold)
					{
						castle->changeGold(-lessGold);
						tile.buildTrap(hw, Trap::POISON_TRAP);
					}
				}
			};
			break;
		case MENU_TRAP:
			action =
			{
				[](MainScene* hw, Tile& tile)
				{
					int lessGold;
					Castle* castle = hw->field_level1->tiles[(int)hw->field_level1->end_enemy.x][(int)hw->field_level1->end_enemy.y].castle;
					if ((lessGold = tile.trap->getPriceLevelUp()) <= castle->gold)
					{
						castle->changeGold(-lessGold);
						tile.trap->levelUp();
					}
				},
				[](MainScene* hw, Tile& tile)
				{
					tile.destroyBuilding(hw);
				}
			};
			break;
		}
		menuSelections = std::vector<ClickableObject>();
		menuSelections.resize(allObjectsPaths[type].size());
		for (int i = 0; i < allObjectsPaths[type].size(); i += 1)
		{
			menuSelections[i] = ClickableObject
			(
				"Isometric Tower defence pack/Sprites/Menu/BurntOrange (1)_04.png",
				t_position + Point(-115, 350 - 220 * i),
				{
					{t_position + Point(-115 - 80, 350 - 220 * i + 80)},
					{t_position + Point(-115 + 80, 350 - 220 * i + 80)},
					{t_position + Point(-115 + 80, 350 - 220 * i - 80)},
					{t_position + Point(-115 - 80, 350 - 220 * i - 80)}
				},
				Point(0.3, 0.3)
			);
		}
		objects = std::vector<GameObject>();
		objects.resize(allObjectsPaths[type].size());
		for (int i = 0; i < allObjectsPaths[type].size(); i += 1)
		{
			objects[i] = GameObject
			(
				allObjectsPaths[type][i],
				t_position + Point(-115, 350 - 220 * i),
				allObjectsScales[type][i]
			);
		}
	};

	void MenuObject::show(MainScene* hw)
	{
		if (is_show == 0)
		{
			is_show = 1;
			for (int i = 0; i < objects.size(); i += 1) {
				objects[i].show(hw, 3);
			}
			for (int i = 0; i < menuSelections.size(); i += 1) {
				menuSelections[i].show(hw, 2);
			}
			for (int i = 0; i < stats.size(); i += 1) {
				stats[i].show(hw, 2);
			}
		}
	}
	void MenuObject::hide(MainScene* hw)
	{
		if (is_show == 1)
		{
			is_show = 0;
			for (int i = 0; i < objects.size(); i += 1) {
				objects[i].hide(hw);
			}
			for (int i = 0; i < menuSelections.size(); i += 1) {
				menuSelections[i].hide(hw);
			}
			for (int i = 0; i < stats.size(); i += 1) {
				stats[i].hide(hw);
			}
		}
	}

}