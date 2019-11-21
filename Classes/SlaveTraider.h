#pragma once
#include "CitizenController.h"
#include "IPayable.h"
#include "Data.h"
#include "Enviroment.h"

class SlaveTraider : public IPayable{
private:

	Sprite* spr;
	SlaveTraider();
	static SlaveTraider* slaveTraider;
	virtual void createCitizen();

public:
	
	static SlaveTraider* getInstance();
	virtual void pay(int&) override;

};