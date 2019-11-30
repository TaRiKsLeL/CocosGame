#pragma once
#include "Collisions.h"
#include "cocos2d.h"
#include "MainMenu.h"
#include "Enviroment.h"
#include "SlaveTraider.h"

USING_NS_CC;

class GameScene : public Scene
{
protected:
	int count = 0;
public:
	static Scene* createScene();
	
	virtual bool init();
	void initUIComponents();
	virtual void update(float) override;

	virtual void removeKeyEventListener(EventListenerKeyboard*);
	virtual void setKeyEventListener(EventListenerKeyboard* , Sprite* );
	
	bool onPlayerContactBegin(PhysicsContact&);
	bool onPlayerContactSeparate(PhysicsContact&);

	bool onBuilderContactBegin(PhysicsContact&);
	bool onBuilderContactSeparate(PhysicsContact&);
	
	bool onEnemyContactBegin(PhysicsContact&);

	void initContactListeners();

	IPayable* getPayableByNode(Node*);
	IAttackable* getAttackableByNode(Node*);
	//virtual void newMenuCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameScene);
};
