#pragma once
#include "cocos2d.h"
#include <vector>
#include "IPayable.h"
#include "Data.h"
#include "Enviroment.h"
#include "FriendlyNPC.h"
//#include "Citizen.h"

USING_NS_CC;

class Citizen :public FriendlyNPC , public IPayable {
private:

public:
	Citizen(Vec2);

	virtual void pay(int&) override;

};


class CitizenController 
{

private:
	vector<Citizen*>* citizens;
	CitizenController();
	static CitizenController* citizenController;
public:
	
	static CitizenController* getInstance();
	void create(Vec2);
	void allMoveRand();
	Citizen* findByPosition(Vec2);
};
