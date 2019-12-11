#pragma once
#include "CitizenController.h"
#include "Player.h"
#include "Payable.h"
#include "Data.h"
#include "Enviroment.h"

class SlaveTraider : public Payable, public ITimeDepended{
private:

	int saledSlaves;

	Sprite* spr;
	SlaveTraider();
	static SlaveTraider* slaveTraider;
	virtual void createCitizen();
	PhysicsBody* createPhysBody();

public:
	
	static SlaveTraider* getInstance();
	virtual void pay(int&) override;
	virtual void timeDependedAction() override;
	virtual void setSelector() override;

};