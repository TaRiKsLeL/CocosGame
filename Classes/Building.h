#pragma once

#include "cocos2d.h"
#include "Payable.h"
#include "ITimeDepended.h"
#include "Data.h"
#include <vector>

//#include "Enviroment.h"

USING_NS_CC;

class Building : public Payable, public ITimeDepended
{
private:

protected:

	Sprite* spr;

	string filename;

	const vector<std::string>* levelsImages;

	int buildingWigth;
	int buildingHeight;

	Direction direction;

	int level{0};
	int lastLevel{ level };
	
	bool isBuilding;
	bool waitForBuilder;

	int nextUpgradeDuration;
	int currentState{0};
	
	virtual PhysicsBody* createPhysBody();
public:

	Building(const vector<std::string>*);

	Sprite* getSprite();
	Vec2 getPosition();

	virtual void pay(int&) = 0;
	void timeDependedAction() override;
	int getLevel();
	void upgrade();
	void setBuildingStatus(bool);
	virtual void specitalUpdateAction();
	virtual void setSelector() override;

	Direction getDirrection();

};

