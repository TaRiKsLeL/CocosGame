#pragma once
#include "cocos2d.h"
#include "Data.h"
#include "Citizen.h"
#include <vector>
#include <stack>
#include "Player.h"

USING_NS_CC;

class UI {
private:

	
	static UI* ui;

	//coin pic and coins amount label

	Sprite* coin;

	Label* coinsAmount;

	//heart

	Sprite* fullHeart;
	Sprite* emptyHeart;

	//citizen pictures
	vector<Sprite*>* selectSprs;
	
	stack<int>* selectSprsPositionX;

	Citizen* currentCitizen;

	UI();
	void initStack();
	void initIcons();

	//other
	

public:

	static UI* getInstance();

	//coins
	Label* getCoinsLabel();

	Sprite* getCoinSprite();

	void createCoin(std::string, int, float, float);

	void createHeart(std::string, std::string, int, float, float);

	void createCoinsLabel(std::string, std::string,int);

	void setCoinsAmountLabel(int);

	Animate* createAnimate(string, int, float, float);

	//citizen pictures methods

	void addCitizenSelectIcons(Citizen*);

	void removeCitizenSelectIcons();

	//other

};