#pragma once

#include "cocos2d.h"
#include "IMoveable.h"
#include "Enviroment.h"
#include "Data.h"

USING_NS_CC;

class Player :private IMoveable {

private:

	struct MoveDirection
	{
		bool left{ false };
		bool right{ false };
	};

	int money;

	MoveDirection direction;
	EventListenerKeyboard* listener;
	Sprite* spr;


	static Player* player;

	Player(const std::string);
	virtual void setKeyListener(void (Player::*onKeyPresssed)());
	virtual void onMoveKeyPressed();
	virtual void onKeyPressedAct();
	virtual void changeMoveDirection(EventKeyboard::KeyCode, bool);
	virtual void setActKeys(EventKeyboard::KeyCode);

public:

	virtual void addMoney(int);
	virtual int& getMoney();
	static Player* getInstance();
	void move() override ;

};

	
