#pragma once
#include "cocos2d.h"
#include <vector>
#include "IPayable.h"
#include "Data.h"
#include "Enviroment.h"
#include "Citizen.h"
#include "UI.h"

USING_NS_CC;


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
