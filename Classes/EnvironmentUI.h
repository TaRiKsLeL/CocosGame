#pragma once

#include "BuildingController.h"

USING_NS_CC;

class EnvironmentUI {
private:
	EnvironmentUI();

	static EnvironmentUI* environmentUI;
	Node* baseNode;
	Sprite* skySpr;
	Sprite* nightSkySpr;
	Sprite* cloudsSpr;

	map<Sprite*, float> parallaxMap;

	vector<Sprite*> trees;
	stack<Sprite*>* deleteTreesStack;
	bool pointIntersectsTree(float);

	MoveDirection windDirection;

public:
	
	Node* getBaseNode();
	map<Sprite*, float>* getParallaxMap();
	MoveDirection getWindDir();

	Action* createMoveByActionCloud(int speed,int dist);

	void startRotateSun();
	void updateBackground();
	void setBackground();
	void setDarkness();	
	void setSeamlessSprite(string path, float speed,int yOffset, int zOrder);

	void generateTrees();
	void updateTrees();
	void createFence(KingdomBorders*);

	static EnvironmentUI* getInstance();
};