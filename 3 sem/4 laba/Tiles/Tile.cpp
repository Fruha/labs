#include "Tiles/Tile.h"
#include "Tiles/Field.h"
#include "Buildings/Tower/Tower.h"

namespace game 
{
	void Tile::buildTower(MainScene* hw, Tower::Type type)
	{
		if (type == Tower::Type::CLASSIC_TOWER)
		{
			state = CANT_BUILD_TOWER;
			tower = new Tower(position + Point(0, Field::tile_size.y), { 0.06, 0.06 },
				{ 
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Red tower/block(4).png", position + Point(0, Field::tile_size.y), Point(0.06,0.06)),
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Red tower/block(2).png", position + 1.5 * Point(0, Field::tile_size.y), Point(0.06,0.06)),
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Red tower/block(9).png", position + 2 * Point(0, Field::tile_size.y), Point(0.06,0.06))
				}, Tower::CLASSIC_TOWER
				);
			tower->show(hw, 1);
		}
		if (type == Tower::Type::MAGIC_TOWER)
		{
			state = CANT_BUILD_TOWER;
			tower = new Tower(position + Point(0, Field::tile_size.y), { 0.06, 0.06 },
				{ 
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Purple tower/block(4).png", position + Point(0, Field::tile_size.y), Point(0.06,0.06)),
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Purple tower/block(2).png", position + 1.5 * Point(0, Field::tile_size.y), Point(0.06,0.06)),
					PartOfTower("Isometric Tower defence pack/Sprites/Tower tiles/Purple tower/block(9).png", position + 2 * Point(0, Field::tile_size.y), Point(0.06,0.06))
				}, Tower::MAGIC_TOWER
				);
			tower->show(hw, 1);
		}
	}

	void Tile::buildTrap(MainScene* hw, Trap::Type type)
	{
		if (type == Trap::POISON_TRAP)
		{
			state = CANT_BUILD_TRAP;
			trap = new Trap(position + Point(0, Field::tile_size.y), Trap::POISON_TRAP, this);
			trap->show(hw);
		}
	}

	void Tile::destroyBuilding(MainScene* hw) 
	{
		if (tower != nullptr)
		{
			state = CAN_BUILD_TOWER;
			tower->hide(hw);
			delete(tower);
			tower = nullptr;
		}
		if (trap != nullptr)
		{
			state = CAN_BUILD_TRAP;
			trap->hide(hw);
			delete(trap);
			trap = nullptr;
		}
	};

	void Tile::buildCastle(MainScene* hw, int life, int gold)
	{
		castle = new Castle("Isometric Tower defence pack/Sprites/Castle/Castle_01.png", position + Point(0, Field::tile_size.y + 8.f), life, gold, { 0.1, 0.1 });
		castle->show(hw, 1);
		castle->goldObject->show(hw, 2);
		castle->lifeObject->show(hw, 2);
	}

	void Tile::buildLair(MainScene* hw)
	{
		lair = new Lair("Isometric Tower defence pack/Sprites/Lair/Crystal_01.png", position + Point(0, Field::tile_size.y + 15.f), { 0.1, 0.1 });
		lair->show(hw, 1);

	}


}