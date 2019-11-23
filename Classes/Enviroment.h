#pragma once
#include "Player.h"
#include "GameScene.h"
#include "GameTime.h"
#include "cocos2d.h"
#include "Data.h"
#include "BuildingController.h"
#include "SlaveTraider.h"
#include "KingdomBorders.h"

USING_NS_CC;

class Enviroment {
private:

	KingdomBorders borders;

	static Enviroment* enviroment;
	Sprite* groundSpr;
	Scene* scene;

	void addComponents();
public:

	static Enviroment* getInstance();
	
	void setScene(Scene*);
	void setGroundSpr(const std::string);

	double getGroundWidth();
	
	Scene* getScene();

};


