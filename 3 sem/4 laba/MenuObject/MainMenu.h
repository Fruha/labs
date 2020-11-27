#pragma once
#include "Abstract/GameObject.h"
#include "MenuObject/MenuObject.h"


namespace game 
{
	class MainMenu : public GameObject 
	{
	private:
	protected:
	public:
		MenuObject::Type is_show_type;
		std::map <MenuObject::Type, MenuObject*> menu;
		MainMenu(Point t_position);

		void show(MainScene* hw, MenuObject::Type type);
		void hide(MainScene* hw);
	};
}