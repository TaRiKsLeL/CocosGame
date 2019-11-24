#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Builder.h"
#include "UI.h"

USING_NS_CC;


class BuilderController
{

private:
	vector<Builder*>* builders;
	BuilderController();
	static BuilderController* builderController;
public:

	static BuilderController* getInstance();
	void create(Vec2);
	void allMoveRand();
	Builder* findByPosition(Vec2);
	Builder* findClosestFree(Vec2);
};
