#pragma once

#include "cocos2d.h"
#include "IMoveable.h"
#include "IPayable.h"
#include "ITimedepended.h"
#include "Enviroment.h"
#include "Data.h"
#include "CitizenController.h"
#include "UI.h"

USING_NS_CC;

class Player :private IMoveable {

private:

	int money;
	int hp;

	bool isFocused;
	bool isDisabledChoseRoleListener;

	MoveDirection direction;
	
	EventListenerKeyboard* moveListener;
	EventListenerKeyboard* buyListener;
	EventListenerKeyboard* choseRoleListener;
	
	Sprite* spr;
	
	IPayable* objInFocus;

	static Player* player;

	Player(const std::string);
	
	void setCamera();
	
	PhysicsBody* createPhysBody();

	void initMoveListener();
	void initBuyListener();
	void initChoseRoleListener();

	void changeMoveDirection(EventKeyboard::KeyCode, bool);
	
public:
	static Player* getInstance();

	void addMoney(int);
	int& getMoney();

	void addHP(int);
	int& getHP();

	void addChild(Node*);
	void removeAllChildren();

	void move() override ;
	
	void disableFocusBuyListener();
	void disableBuyListener();
	
	void setPayable(IPayable*);
	bool checkFocusedObj(IPayable*);
	bool focused();

	void enableChoseRoleListener();
};

	
