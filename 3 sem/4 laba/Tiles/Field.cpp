#include <string>
#include "Tiles/Field.h"

namespace game {
	Point Field::start = Point(100.f, 400.f);
	Point Field::tile_size = Point(59.f, 34.f);


	Field::Field() {

	}
	Field::Field(int level, MainScene* t_hw)
	{
		hw = t_hw;
		if (level == 1) 
		{
			std::string level1[len][width] =
			{{"Enviroument tiles/ground.png", "Road tiles/road(13).png"     , "Enviroument tiles/ground.png", "River tiles/river(9).png"    , "River tiles/river(10).png"   , "River tiles/river(10).png"   , "River tiles/river(8).png"             , "Enviroument tiles/ground.png"         , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/roads on water/road(4).png", "Road tiles/road(14).png"              , "Road tiles/road(4).png"      , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "River tiles/river(11).png"            , "Enviroument tiles/ground.png"         , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Road tiles/road(3).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(5).png"      , "River tiles/river(9).png"             , "River tiles/river(8).png"             , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "River tiles/river(11).png"            , "Road tiles/road(15).png"     , "Enviroument tiles/ground.png"},
			 {"Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"     , "Road tiles/road(14).png"              , "Road tiles/roads on water/road(4).png", "Road tiles/road(5).png"      , "Enviroument tiles/ground.png"},
			 {"River tiles/river(8).png"    , "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "River tiles/river(9).png"             , "River tiles/river(10).png"   , "River tiles/river(8).png"},
			 {"River tiles/river(11).png"   , "Enviroument tiles/ground.png", "Road tiles/road(15).png"     , "Enviroument tiles/ground.png", "Road tiles/road(2).png"      , "Road tiles/road(14).png"     , "Road tiles/road(14).png"              , "Road tiles/road(4).png"               , "Enviroument tiles/ground.png", "River tiles/river(9).png"},
			 {"River tiles/river(11).png"   , "Enviroument tiles/ground.png", "Road tiles/road(3).png"      , "Road tiles/road(14).png"     , "Road tiles/road(5).png"      , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "Road tiles/road(15).png"              , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"},
			 {"River tiles/river(9).png"    , "River tiles/river(8).png"    , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"         , "Road tiles/road(11).png"              , "Enviroument tiles/ground.png", "Enviroument tiles/ground.png"}};
            for (int i1 = 0; i1 < len; i1 += 1)
            {
                for (int i2 = 0; i2 < width; i2 += 1)
                {
					Tile temp("Isometric Tower defence pack/Sprites/" + level1[len - i2 - 1][i1],
						Point(start.x + (i1 + i2) * tile_size.x, start.y + tile_size.y * (i2 - i1)), 
						{{start.x + tile_size.x * (i1 + i2 - 1),start.y + 24.f + tile_size.y * (i2 - i1)},
						 {start.x + tile_size.x * (i1 + i2)    ,start.y + 24.f + tile_size.y * (i2 - i1 + 1)},
						 {start.x + tile_size.x * (i1 + i2 + 1),start.y + 24.f + tile_size.y * (i2 - i1)},
						 {start.x + tile_size.x * (i1 + i2)    ,start.y + 24.f + tile_size.y * (i2 - i1 - 1)}},
						{ 0.1,0.1 }
						);
					if (temp.path.find("road") != -1) 
					{
						temp.isRoad = 1;
					}
					if (temp.path == "Isometric Tower defence pack/Sprites/Enviroument tiles/ground.png") 
					{
						temp.state = Tile::CAN_BUILD_TOWER;
					}
					if (temp.path.find("Road tiles/road") != -1 && temp.path.find("water") == -1)
					{
						temp.state = Tile::CAN_BUILD_TRAP;
					}
					for (int i = 10; i < 14; i += 1) 
					{
						if (temp.path == ("Isometric Tower defence pack/Sprites/Road tiles/road(" + std::to_string(i) + ").png")) 
						{
							temp.state = Tile::CANT_BUILD;
						}
					}
					add_tile(temp, i1, i2);
                }
            }
			

		}
	}
	void Field::show()
	{
		for (int i1 = 0; i1 < len; i1 += 1)
		{
			for (int i2 = 0; i2 < width; i2 += 1)
			{
				if (tiles[i1][i2].sprite != nullptr) 
				{
					tiles[i1][i2].show(hw, -i2);
				}
			}
		}
	}

	void Field::add_tile(Tile tile, int x, int y)
	{
		if (x < 0 || x >= len)
		{
			throw("Invalid x");
		}
		if (y < 0 || y >= width)
		{
			throw("Invalid y");
		}
		tiles[x][y] = tile;
	}
	bool Field::tileInField (Point tile)
	{
		return (tile.x >= 0 && tile.x < len && tile.y >= 0 && tile.y < width);
	};
	float Field::mapDistance(Point p1, Point p2)
	{
		Point temp = p2 - p1;
		return (Point(temp.x, temp.y / Field::tile_size.y * Field::tile_size.x).length());
	}

}