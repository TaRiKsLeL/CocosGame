#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"
#include "Citizen.h"
#include "UI.h"
#include "BuilderController.h"
#include "Player.h"

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
	void setNewRole(SprTag , IPayable*);
	void deleteByPos(Vec2);
	Citizen* findByPosition(Vec2);
};
