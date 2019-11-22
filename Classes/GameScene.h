#pragma once
#include "cocos2d.h"
#include "MainMenu.h"
#include "Enviroment.h"

USING_NS_CC;

class GameScene : public Scene
{
protected:

public:
	static Scene* createScene();
	
	virtual bool init();
	virtual void update(float) override;
	virtual void removeKeyEventListener(EventListenerKeyboard*);
	virtual void setKeyEventListener(EventListenerKeyboard* , Sprite* );
	bool onContactBegin(PhysicsContact&);
	bool onContactSeparate(PhysicsContact&);

	//virtual void newMenuCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameScene);
};
