#pragma once
#include "cocos2d.h"
#include "Data.h"
#include "CitizenController.h"
#include <vector>
#include <stack>

USING_NS_CC;

class UI {
private:

	//citizen pictures
	static UI* ui;

	vector<Sprite*>* selectSprs;
	
	stack<int>* selectSprsPositionX;

	Citizen* currentCitizen;

	UI();
	void initStack();
	void initIcons();

	//other
	

public:

	static UI* getInstance();

	//citizen pictures methods

	void addCitizenSelectIcons(Citizen*);

	void removeCitizenSelectIcons();

	//other

};