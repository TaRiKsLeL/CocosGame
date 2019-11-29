#pragma once
#include "Player.h"
#include "GameScene.h"
#include "GameTime.h"
#include "cocos2d.h"
#include "Data.h"
#include "SlaveTraider.h"
#include "KingdomBorders.h"
#include "EnvironmentUI.h"

USING_NS_CC;

class Enviroment {
private:

	static Enviroment* enviroment;

	KingdomBorders* borders;

	Sprite* groundSpr;
	Scene* scene;

	void addComponents();
public:

	static Enviroment* getInstance();
	
	void setScene(Scene*);
	void setGroundSpr(const std::string);
	void setBorders(KingdomBorders* borders);

	KingdomBorders* getBorders();
	double getGroundWidth();
	
	Scene* getScene();

};


