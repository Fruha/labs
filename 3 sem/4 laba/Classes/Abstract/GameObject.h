#pragma once
#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

namespace game 
{
	class GameObject 
	{
	private:
	protected:
	public:
		Point position;
		std::string path = "";
		Sprite* sprite = nullptr;
		Label* label = nullptr;
		int is_show = 0;

		GameObject() :
			position({ 0,0 })
		{};
		GameObject(Point t_position, Point scale = { 1,1 }) :
			position(t_position)
		{
			setPosition(t_position, scale);
		};
		GameObject(std::string t_path, Point t_position, Point scale = { 1,1 }) :
			path(t_path),
			sprite(Sprite::create(path))
		{
			setPosition(t_position, scale);
		};
		GameObject(std::string t_text, Point t_position, int font, Point scale = { 1,1 }) :
			label(Label::createWithTTF(t_text, "fonts/Marker Felt.ttf", font))
		{
			setPosition(t_position, scale);
		};

		GameObject(std::string t_path, Point t_positionSprite, std::string t_text, Point t_positionLabel, int font, Point scaleSprite = { 1,1 }, Point scaleLabel = { 1,1 }) :
			sprite(Sprite::create(t_path)),
			label(Label::createWithTTF(t_text, "fonts/Marker Felt.ttf", font))
		{
			sprite->setPosition(t_positionSprite);
			sprite->setScale(scaleSprite.x, scaleSprite.y);
			label->setPosition(t_positionLabel);
			label->setScale(scaleLabel.x, scaleLabel.y);
		};

		void setPosition(Point t_position, Point scale);
		void show(MainScene* hw, int show_level);
		void hide(MainScene* hw);
	};
}