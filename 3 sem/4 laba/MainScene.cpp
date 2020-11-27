#include <iostream>
#include "MainScene.h"
#include "Tiles/Field.h"
#include "MenuObject/MenuObject.h"
#include "MenuObject/MainMenu.h"
#include <numbers>
#include "ui/CocosGUI.h"

USING_NS_CC;
const Point game::MainScene::windowSize = Point(1600.f, 900.f);

Scene* game::MainScene::createScene()
{
    return MainScene::create();
}

bool game::MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    mainMenu = new MainMenu(Point(1425, 400));
    this->scheduleUpdate();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::OnTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    field_level1 = new Field(1, this);
    field_level1->show();
    field_level1->tiles[(int)field_level1->end_enemy.x][(int)field_level1->end_enemy.y].buildCastle(this, 10, 10);
    field_level1->tiles[(int)field_level1->start_enemy.x][(int)field_level1->start_enemy.y].buildLair(this);
    field_level1->tiles[(int)field_level1->start_enemy.x][(int)field_level1->start_enemy.y].lair->createWay(field_level1);
    
    //auto myLabel = Label::createWithSystemFont("Hello", "Arial", 40);
    //myLabel->setPosition(Vec2(visibleSize.width/2 , visibleSize.height - 50));
    //this->addChild(myLabel, 1);
 
    auto button = ui::Button::create("Isometric Tower defence pack/Sprites/Menu/resumeButton.png");
    button->setPosition(Point(1500, 100));
    button->setScale(0.2, 0.2);
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (isPaused != 1) 
            {
                Director::getInstance()->pause();
                isPaused = 1;
            }
            else
            {
                Director::getInstance()->resume();
                isPaused = 0;
            }
            break;
        default:
            break;
        }
        });

    this->addChild(button);

    return true;
}

void game::MainScene::update(float dt)
{
    Lair* lair = field_level1->tiles[(int)field_level1->start_enemy.x][(int)field_level1->start_enemy.y].lair;
    if ((int)(currentTime / lair->rate) == (int)((currentTime + dt) / lair->rate) - 1) 
    {
        lair->addEnemy(this, field_level1, ((int)std::pow(5 * (currentTime / 20 + 1), 1.3)));
    }
    currentTime += dt;
    Point tileLair = field_level1->start_enemy;
    for (int i1 = 0; i1 < field_level1->len; i1 += 1)
    {
        for (int i2 = 0; i2 < field_level1->width; i2 += 1)
        {
            if (field_level1->tiles[i1][i2].tower != nullptr)
            {
                Enemy* temp = field_level1->tiles[i1][i2].tower->findCloseEnemyToCastle(this);
                field_level1->tiles[i1][i2].tower->fire(this, temp, Color4B::RED);
            }
            if (field_level1->tiles[i1][i2].trap != nullptr)
            {
                Enemy* temp = field_level1->tiles[i1][i2].trap->findCloseEnemyToCastle(this);
                field_level1->tiles[i1][i2].trap->fire(this, temp);
            }
        }
    }
    std::list<Enemy*>tempEnemies(lair->enemies);
    std::list<Enemy*>::iterator it;

    for (it = tempEnemies.begin(); it != tempEnemies.end(); it++) 
    {
        (*it)->updateEffects(this, dt);
    }


}

bool game::MainScene::OnTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event1)
{
    CCLOG("x = %f , y = %f", touch->getLocation().x, touch->getLocation().y);
    for (int i1 = 0; i1 < field_level1->len; i1 += 1)
    {
        for (int i2 = 0; i2 < field_level1->width; i2 += 1)
        {
            if (field_level1->tiles[i1][i2].PointInPolygon(touch->getLocation()))
            {
                if (field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y].state == Tile::CANT_BUILD_TOWER)
                {
                    (field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y].tower->hideArea(this));
                }
                if (field_level1->selectedTile != Point(i1, i2) && (field_level1->tiles[i1][i2].state != Tile::CANT_BUILD))
                {
                    field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y].sprite->runAction(TintTo::create(0.f, 255.f, 255.f, 255.f));
                    if (field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y].trap != nullptr) 
                    {
                        field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y].trap->show(this);
                    }
                    field_level1->tiles[i1][i2].sprite->runAction(TintTo::create(0.f, 0.f, 102.f, 255.f));
                    field_level1->selectedTile = { (float)i1,(float)i2 };
                }
                if (field_level1->tiles[i1][i2].state != Tile::CANT_BUILD && mainMenu->is_show == 1)
                {
                    mainMenu->hide(field_level1->hw);
                }
                if (field_level1->tiles[i1][i2].state != Tile::CANT_BUILD && mainMenu->is_show == 0) 
                {
                    mainMenu->show(field_level1->hw, (MenuObject::Type)(field_level1->tiles[i1][i2].state - 1));
                }
                if (field_level1->tiles[i1][i2].state == Tile::CANT_BUILD_TOWER) 
                {
                    (field_level1->tiles[i1][i2].tower->showArea(this, 1));
                }

            }
        }
    }

    if (mainMenu->is_show == 1) 
    {
        for (int i1 = 0; i1 < mainMenu->menu[mainMenu->is_show_type]->menuSelections.size(); i1 += 1)
        {
            if (mainMenu->menu[mainMenu->is_show_type]->menuSelections[i1].PointInPolygon(touch->getLocation()))
            {   
                mainMenu->menu[mainMenu->is_show_type]->action[i1](field_level1->hw, field_level1->tiles[(int)field_level1->selectedTile.x][(int)field_level1->selectedTile.y]);
                mainMenu->hide(field_level1->hw);
                break;
            }
        }
    }
    

    return true;
}

void game::MainScene::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    //CCLOG("x = %f , y = %f", e->getCursorX(),900 + e->getCursorY());
    if (!field_level1->tiles[(int)field_level1->last.x][(int)field_level1->last.y].PointInPolygon(Point(e->getCursorX(), 900 + e->getCursorY())) 
        && field_level1->selectedTile != field_level1->last)
    {
        if (field_level1->tiles[(int)field_level1->last.x][(int)field_level1->last.y].trap == nullptr)
        {
            field_level1->tiles[(int)field_level1->last.x][(int)field_level1->last.y].sprite->runAction(TintTo::create(0.f, 255.f, 255.f, 255.f));
        }
        else 
        {
            field_level1->tiles[(int)field_level1->last.x][(int)field_level1->last.y].trap->show(this);
        }

    }
    for (int i1 = 0; i1 < field_level1->len; i1 += 1)
    {
        for (int i2 = 0; i2 < field_level1->width; i2 += 1)
        {
            if (field_level1->tiles[i1][i2].PointInPolygon(Point(e->getCursorX(), 900 + e->getCursorY())) && field_level1->selectedTile != Point(i1,i2))
            {
                if (field_level1->tiles[i1][i2].is_show == 1) 
                {
                    if (field_level1->tiles[i1][i2].state != Tile::CANT_BUILD)
                    {
                        field_level1->tiles[i1][i2].sprite->runAction(TintTo::create(0.f, 0.f, 255.f, 0.f));
                    } 
                    else
                    {
                        field_level1->tiles[i1][i2].sprite->runAction(TintTo::create(0.f, 255.f, 51.f, 0.f));                     
                    }
                }
                field_level1->last = { (float)i1, (float)i2 };
            }
        }
    }

}

void game::MainScene::menuCloseCallback(Ref* pSender)
{

    Director::getInstance()->end();
}