#include "MenuObject/MainMenu.h"

namespace game 
{
	MainMenu::MainMenu(Point t_position) :
		GameObject(t_position)
	{};

	void MainMenu::show(MainScene* hw, MenuObject::Type type)
	{
		if (is_show == 0) 
		{
			is_show = 1;
			is_show_type = type;
			menu[type] = new MenuObject(hw, position, type);
			menu[type]->show(hw);
		}
	};

	void MainMenu::hide(MainScene* hw)
	{
		if (is_show == 1)
		{
			is_show = 0;
			if (menu[is_show_type] != nullptr)
			{
				menu[is_show_type]->hide(hw);
				delete(menu[is_show_type]);
				menu[is_show_type] = nullptr;
			}
		}
	};
}