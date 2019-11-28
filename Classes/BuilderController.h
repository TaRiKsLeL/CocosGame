#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Builder.h"
#include "UI.h"
#include "BaseController.h"

USING_NS_CC;


class BuilderController
{

private:

	BuilderController();
	BaseController<Builder> controller;
	static BuilderController* builderController;
	Builder* findCosestFree(Vec2);


public:

	static BuilderController* getInstance();
	void create(Vec2);
	void allMoveRand();
	void deleteByPos(Vec2);
	Builder* findByPosition(Vec2);
	
	void setPositionToBuild(Vec2);

};
