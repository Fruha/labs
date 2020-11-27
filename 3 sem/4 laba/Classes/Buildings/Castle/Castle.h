#pragma once
#include "Abstract/GameObject.h"

namespace game 
{
	class Castle : public GameObject 
	{
	private:
	protected:
	public:
		bool is_alive = 1;
		GameObject* lifeObject = nullptr;
		int life;
		GameObject* goldObject = nullptr;
		int gold;

		Castle(std::string t_path, Point t_position, int t_life, int t_gold, Point scale = { 1,1 });

		void changeLife(MainScene* hw, int change);
		void changeGold(int change);

	};
}