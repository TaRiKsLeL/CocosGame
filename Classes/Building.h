#pragma once

#include "cocos2d.h"
#include "IPayable.h"
#include "ITimeDepended.h"
#include "Data.h"
#include <vector>
//#include "Enviroment.h"

USING_NS_CC;

class Building : public IPayable, public ITimeDepended
{
private:
	
protected:

	struct Direction
	{
		bool left{ false };
		bool right{ false };
	};

	Sprite* spr;

	string filename;

	const vector<std::string>* levelsImages;

	int buildingWigth;
	int buildingHeight;

	Direction direction;

	int level{0};
	int lastLevel{ level };
	bool isBuilding;
	int nextUpgradeDuration;
	int currentState{0};
	
	PhysicsBody* createPhysBody();
public:

	Building(std::string,const int, const int);
	Building(const vector<std::string>*);

	Sprite* getSprite();
	

	virtual void pay(int&) = 0;
	void timeDependedAction() override;
	int getLevel();
	void upgrade();

};

