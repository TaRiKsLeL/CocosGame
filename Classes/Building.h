#pragma once

#include "cocos2d.h"
#include "IPayable.h"
#include "ITimeDepended.h"

USING_NS_CC;

class Building : public IPayable, public ITimeDepended
{
private:
	enum BuildingType {
		TOWER,
		WALL,
		MINE,
		CASTLE
	};


protected:

	Sprite* spr;

	int level{0};
	int lastLevel{ level };
	bool isBuilding;
	int nextUpgradeDuration;
	int currentState{0};
	
	void increaseLevel();

public:

	void pay(int&) override;
	void timeDependedAction() override;
	
	int getLevel();

	void upgrade();

};