#include "Lair.h"
#include "Tiles/Tile.h"
#include "Tiles/Field.h"
#include <algorithm>
#include "Abstract/ClickableObject.h"

namespace game
{
	Lair::Lair(std::string t_path, Point t_position, Point t_scale) :
		GameObject(t_path, t_position, t_scale)
	{};

	FiniteTimeAction* Lair::createWayOneTile(Point start, Point end, Point tile, Field* field)
	{
		auto dist = [](Point p1, Point p2)->double {return sqrt(((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y))); };
		Point startPoint = field->tiles[(int)tile.x][(int)tile.y].ClickPoligon[0];
		Point tempVec1 = Field::tile_size / 2;
		Point tempVec2 = Point(Field::tile_size.x, -Field::tile_size.y) / 2;
		
		if (
			(start == Point(0, 1) && end == Point(1, 0))
			|| (start == Point(1, 0) && end == Point(0, 1))
			|| (start == Point(0, 1) && end == Point(1, 2))
			|| (start == Point(1, 2) && end == Point(0, 1))
			|| (start == Point(1, 2) && end == Point(2, 1))
			|| (start == Point(2, 1) && end == Point(1, 2))
			|| (start == Point(2, 1) && end == Point(1, 0))
			|| (start == Point(1, 0) && end == Point(2, 1))
			)
		{
			ccBezierConfig bezier;
			Point p1, p2, p3;
			p1 = startPoint + start.x * tempVec2 + start.y * tempVec1;
			p2 = startPoint + tempVec2 + tempVec1;
			p3 = startPoint + end.x * tempVec2 + end.y * tempVec1;
			bezier.controlPoint_1 = (p1 + p2) / 2 + Point(0, height);
			bezier.controlPoint_2 = (p2 + p3) / 2 + Point(0, height);
			bezier.endPosition = p3 + Point(0, height);
			return (FiniteTimeAction*)BezierTo::create(3.1415/4/speed, bezier);
		}
		else
		{
			Point p1, p2;
			p1 = startPoint + start.x * tempVec2 + start.y * tempVec1 + Point(0, height);
			p2 = startPoint + end.x * tempVec2 + end.y * tempVec1 + Point(0, height);
			return (FiniteTimeAction*)MoveTo::create(dist(p1, p2)/dist(Point(0,0),tempVec1 * 2)/speed, p2);
		}
	}

	void Lair::createWay(Field* field) 
	{
		std::vector < std::vector <int> > pathLen(Field::len, std::vector <int>(Field::width));

		for (int i1 = 0; i1 < field->len; i1 += 1)
		{
			for (int i2 = 0; i2 < field->width; i2 += 1)
			{
				pathLen[i1][i2] = INT_MAX - 100;
			}
		}
		pathLen[(int)field->end_enemy.x][(int)field->end_enemy.y] = 0;

		findWay(field->end_enemy, field, pathLen);
		cocos2d::Vector<FiniteTimeAction*> tempWay(pathLen[(int)field->start_enemy.x][(int)field->start_enemy.y] + 3);
		backWay(field->start_enemy, Point(0, 0), field, pathLen, tempWay);
	}
	void Lair::backWay(Point tile, Point previousStep, Field* field, std::vector < std::vector <int> >& pathLen, cocos2d::Vector<FiniteTimeAction*>& tempWayDamage)
	{
		if (pathLen[(int)tile.x][(int)tile.y] == 0)
		{
			tempWayDamage.insert(tempWayDamage.capacity() - 3, createWayOneTile(Point(1, 1) - previousStep, Point(1, 1), tile, field));
			FiniteTimeAction* giveDamage = CallFunc::create([field]() {
					field->tiles[(int)field->end_enemy.x][(int)field->end_enemy.y].castle->changeLife(field->hw, -1);
					field->tiles[(int)field->start_enemy.x][(int)field->start_enemy.y].lair->enemies.pop_front();
			    });
			tempWayDamage.insert(tempWayDamage.capacity() - 2, giveDamage);
			tempWayDamage.insert(tempWayDamage.capacity() - 1, RemoveSelf::create());
			cocos2d::Vector<FiniteTimeAction*> tempWay = tempWayDamage;
			tempWay.popBack();
			tempWay.popBack();
			tempWay.pushBack(RemoveSelf::create());
			//tempWay.back()->retain();
			way = Sequence::create(tempWay);
			way->retain();
			wayWithDamage = Sequence::create(tempWayDamage);
			wayWithDamage->retain();
			return;
		}
		std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
		for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
		{
			Point tile2;
			tile2 = tile + tempPoints[i1];
			if (field->tileInField(tile2))
			{
				if (pathLen[(int)tile2.x][(int)tile2.y] + 1 == pathLen[(int)tile.x][(int)tile.y])
				{
					tempWayDamage.insert(tempWayDamage.capacity() - pathLen[(int)tile.x][(int)tile.y] - 3, createWayOneTile(Point(1, 1) - previousStep, Point(1, 1) + tempPoints[i1], tile, field));
					tempWayDamage.back()->retain();
					backWay(tile2, tempPoints[i1], field, pathLen, tempWayDamage);
				}
			};
		}
	};

	void Lair::minWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen)
	{
		if (field->tileInField(tile))
		{
			if (field->tiles[(int)tile.x][(int)tile.y].isRoad == 1)
			{
				std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
				for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
				{
					Point tile2;
					tile2 = tile + tempPoints[i1];
					if (field->tileInField(tile2) && field->tiles[(int)(tile2.x)][(int)(tile2.y)].isRoad == 1)
					{
						pathLen[(int)tile.x][(int)tile.y] = std::min(pathLen[(int)(tile2.x)][(int)(tile2.y)] + 1, pathLen[(int)tile.x][(int)tile.y]);
					}
				}
			}
		}


	};
	void Lair::findWay(Point tile, Field* field, std::vector < std::vector <int> >& pathLen)
	{
		if (field->tileInField(tile))
		{
			std::vector<Point> tempPoints = { {0,1},{1,0},{0,-1},{-1,0} };
			for (int i1 = 0; i1 < tempPoints.size(); i1 += 1)
			{
				Point tile2;
				tile2 = tile + tempPoints[i1];
				if (field->tileInField(tile2))
				{
					if ((pathLen[(int)tile.x][(int)tile.y] < pathLen[(int)tile2.x][(int)tile2.y] - 1) && (field->tiles[(int)tile2.x][(int)tile2.y].isRoad == 1))
					{
						minWay(tile2, field, pathLen);
						findWay(tile2, field, pathLen);
					}
				};
			}


		}
	};
	void Lair::addEnemy(MainScene* hw, Field* field, int t_life) {
		Enemy* enemy = new Enemy(
			"Isometric Tower defence pack/Sprites/UFO/red ufo.png",
			Point(field->tiles[(int)field->start_enemy.x][(int)field->start_enemy.y].sprite->getPosition() + Point(0, 24.f) + Point(0, 15.f)),
			way,
			wayWithDamage,
			t_life,
			{ 0.15,0.15 }
		);
		enemy->showAll(hw, 1);
		enemy->moveAllPath();
		enemy->lifeObject->label->retain();
		enemy->sprite->retain();
		enemies.push_back(enemy);
	};
}