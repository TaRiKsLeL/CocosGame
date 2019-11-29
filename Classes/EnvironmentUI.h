#pragma once

#include "BuildingController.h"

USING_NS_CC;

class EnvironmentUI {
private:

	static EnvironmentUI* environmentUI;


public:
	vector<Sprite*> trees;
	stack<Sprite*>* deleteTreesStack;
	bool pointIntersectsTree(float);

	void generateTrees();
	void updateTrees();
	void createFence(KingdomBorders*);

	static EnvironmentUI* getInstance();
};