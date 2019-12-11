#pragma once
#include "cocos2d.h"
#include "Data.h"
#include "Citizen.h"
#include <vector>
#include <stack>
#include "Player.h"
#include "ui/CocosGUI.h"


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

	Animate* emptyHeartAnimate;

	//citizen pictures
	vector<Sprite*>* selectSprs;
	
	stack<int>* selectSprsPositionX;

	Citizen* currentCitizen;

	Sprite* gameOverSprite;

	UI();
	void initStack();
	void initIcons();

	//other
	

public:

	void addMark(Sprite*);
	void addHummer(Sprite*);
	Sprite* getSelector(Sprite*);

	static UI* getInstance();

	//coins
	Label* getCoinsLabel();

	Sprite* getCoinSprite();

	void createCoin(std::string, int, float, float);

	void createCoinsLabel(std::string, std::string,int);

	void createVignette(string, int);

	void setCoinsAmountLabel(int);

	//heart

	void createHeart(std::string, std::string, int, float, float);

	void updateHeartLogo(int);

	Animate* createAnimate(string, int, float, int, float);

	//citizen pictures methods

	void addCitizenSelectIcons(Citizen*);

	void removeCitizenSelectIcons();

	//game over


	void setGameOverSprite(string);

	EventListenerKeyboard* toMainSceneListener;
	void initMainSceneListener();

	//other

};