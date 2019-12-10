#pragma once

#include "BuildingController.h"

USING_NS_CC;

class EnvironmentUI {
private:

	static EnvironmentUI* environmentUI;
	Sprite* skySpr;
	Sprite* cloudsSpr;
	vector<Sprite*> trees;
	stack<Sprite*>* deleteTreesStack;
	bool pointIntersectsTree(float);
	EnvironmentUI();
public:
	
	void startRotateSun();
	void updateBackground();
	void setBackground();

	void generateTrees();
	void updateTrees();
	void createFence(KingdomBorders*);

	static EnvironmentUI* getInstance();
};