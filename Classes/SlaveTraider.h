#pragma once
#include "CitizenController.h"
#include "Player.h"
#include "IPayable.h"
#include "Data.h"
#include "Enviroment.h"

class SlaveTraider : public IPayable{
private:

	Sprite* spr;
	SlaveTraider();
	static SlaveTraider* slaveTraider;
	virtual void createCitizen();
	PhysicsBody* createPhysBody();

public:
	
	static SlaveTraider* getInstance();
	virtual void pay(int&) override;

};