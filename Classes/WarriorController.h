#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Warrior.h"
#include "BaseController.h"

#include "UI.h"

USING_NS_CC;


class WarriorController
{

private:
	BaseController<Warrior> controller;
	WarriorController();
	static WarriorController* warriorController;
public:

	static WarriorController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void deleteByPos(Vec2);
	Warrior* findByPosition(Vec2);
	Warrior* findByNode(Node*);
	void moveToWall();

};
