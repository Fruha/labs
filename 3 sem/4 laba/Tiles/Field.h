#pragma once
#include <string>
#include "Tiles/Tile.h"
#include "MainScene.h"

namespace game {
	
	class Field
	{
	private:
	public:
		MainScene* hw = nullptr;
		Point last;
		bool isSelected = 0;
		Point selectedTile;
		static Point start;
		static Point tile_size;
		const static int len = 10;
		const static int width = 10;
		Tile tiles[len][width];
		Point start_enemy = Point(1, 9);
		Point end_enemy = Point(7, 0);


		Field();
		Field(int level, MainScene* t_hw);
		
		float mapDistance(Point p1, Point p2);
		void add_tile(Tile tile, int x, int y);
		bool tileInField(Point tile);
		void show();

	};

}
