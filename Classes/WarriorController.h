#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Warrior.h"
#include "BaseController.h"

#include "UI.h"

USING_NS_CC;


class WarriorController : public ITimeDepended
{
	
private:
	BaseController<Warrior> controller;
	WarriorController();
	static WarriorController* warriorController;
	bool m_areFree;
public:

	static WarriorController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void allMoveStop();
	void deleteByPos(Vec2);
	void removeTargetByTargetPosition(Vec2);
	bool areFree();

	Warrior* findByPosition(Vec2);
	Warrior* findByNode(Node*);
	void moveToWall();
	virtual void timeDependedAction() override;

};

