#pragma once

#include "cocos2d.h"
#include "IMoveable.h"
#include "IPayable.h"
#include "ITimedepended.h"
#include "Enviroment.h"
#include "Data.h"
#include "CitizenController.h"

USING_NS_CC;

class Player :private IMoveable {

private:

	int money;

	bool isFocused;
	bool deleteListener;

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

	void move() override ;
	
	void disableFocusBuyListener();
	void disableBuyListener();
	
	void setPayable(IPayable*);
	bool checkFocusedObj(IPayable*);
	bool focused();

	void enableSelectRoleListener();
};

	
