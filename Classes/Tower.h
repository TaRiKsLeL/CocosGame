#pragma once

#include "Building.h"
#include "Warrior.h"
#include <vector>

class Tower : public Building 
{
	int maxWarriorNum;

	vector<Warrior*> warriorsInsideTower;

public:
	Tower(Direction ,const vector<std::string>*);

	void addWarrior(Warrior*);
	bool canAddWarrior();

	virtual PhysicsBody* createPhysBody();

	virtual void specitalUpdateAction() override;
	void pay(int&) override;
};