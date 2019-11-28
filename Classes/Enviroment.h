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

	KingdomBorders* borders;

	static Enviroment* enviroment;
	Sprite* groundSpr;
	Scene* scene;

	vector<Sprite*> trees;
	stack<Sprite*>* deleteTreesStack;
	bool pointIntersectsTree(float);

	void addComponents();
public:

	static Enviroment* getInstance();
	
	void setScene(Scene*);
	void setGroundSpr(const std::string);
	void setBorders(KingdomBorders* borders);

	void generateTrees();
	void updateTrees();
	void createFence();

	KingdomBorders* getBorders();
	double getGroundWidth();
	
	Scene* getScene();

};


