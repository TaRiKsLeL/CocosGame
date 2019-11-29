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

	void createCoinsLabel(std::string, std::string,int);

	void setCoinsAmountLabel(int);

	void createHeart(std::string, std::string, int, float, float);

	void updateHeartLogo(int);

	Animate* createAnimate(string, int, float, int, float);

	//citizen pictures methods

	void addCitizenSelectIcons(Citizen*);

	void removeCitizenSelectIcons();

	//other

};

g
vsfd
gv
df
eyr
v
fd
v

egf

v

f
v
c

c
c
c
c

c
c
vyt
e
t
vj
u
j
uf
ju
j
uyjvj

uv
j

vj
u
vju
j
vuvj
u
vj
u
vj
u
cj
cuju

ju
j

u
juuj
u
ju
ju
