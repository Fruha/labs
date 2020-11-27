#include "GameObject.h"

namespace game 
{
	void GameObject::show(MainScene* hw, int show_level)
	{
		if (is_show == 0) 
		{
			is_show = 1;
			if (sprite != nullptr)
			{
				hw->addChild(sprite, show_level);
			}
			if (label != nullptr)
			{
				hw->addChild(label, show_level);
			}
		}
	}
	void GameObject::hide(MainScene* hw)
	{

		if (is_show == 1)
		{
			is_show = 0;
			if (sprite != nullptr)
			{
				hw->removeChild(sprite);
			}
			if (label != nullptr)
			{
				hw->removeChild(label);
			}
		}
	}
	void GameObject::setPosition(Point t_position, Point scale)
	{
		position = t_position;
		if (sprite != nullptr)
		{
			sprite->setScale(scale.x, scale.y);
			sprite->setPosition(position);
		}
		if (label != nullptr)
		{
			label->setScale(scale.x, scale.y);
			label->setPosition(position);
		}
	}
}