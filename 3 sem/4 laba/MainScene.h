#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

namespace game {
    class Field;
    class MenuObject;
    class MainMenu;
    class MainScene : public cocos2d::Scene
    {
    private:
        Sprite* enemy = nullptr;
    public:
        bool isPaused = 0;
        MainMenu* mainMenu = nullptr;
        static const Point windowSize;
        Field* field_level1 = nullptr;
        float currentTime = 0;

        static cocos2d::Scene* createScene();

        virtual bool init();
        void menuCloseCallback(cocos2d::Ref* pSender);

        bool OnTouchBegan(Touch* touch, Event* event1);
        void onMouseMove(Event* event);
        void update(float dt);

        CREATE_FUNC(MainScene);

    };

}

#endif // __MAIN_SCENE_H__
