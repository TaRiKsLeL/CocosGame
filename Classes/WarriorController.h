#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Warrior.h"
#include "UI.h"

USING_NS_CC;


class WarriorController
{

private:
	vector<Warrior*>* warriors;
	WarriorController();
	static WarriorController* warriorController;
public:

	static WarriorController* getInstance();
	void create(Vec2);
	void allMoveRand();
	Warrior* findByPosition(Vec2);
	Warrior* findClosestFree(Vec2);
};
#pragma once
