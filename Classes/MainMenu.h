
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void newGameCallback(cocos2d::Ref* pSender);
    void settingsCallback(cocos2d::Ref* pSender);
    void mainMenuCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(MainMenu);
};

#endif 
