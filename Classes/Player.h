#pragma once

#include "cocos2d.h"
#include "IMoveable.h"
#include "Enviroment.h"
#include "Data.h"

USING_NS_CC;

class Player : IMoveable {

	struct MoveDirection
	{
		bool left{false};
		bool right{false};
	};

private:

	MoveDirection direction;
	EventListenerKeyboard* listener;
	Sprite* spr;

	static Player* player;

	Player(const std::string);

	void setKeyListener();
	void onKeyMove();
	void onKeyPressedAct();
	void setMoveKeys(EventKeyboard::KeyCode, bool);
	void setActKeys(EventKeyboard::KeyCode);

public:

	static Player* getInstance();
	void move() override ;

};

	
