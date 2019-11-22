#pragma once
#include"cocos2d.h"
#include"Data.h"

USING_NS_CC;

class FriendlyNPC {

protected:

	Sprite* spr;
	bool isActive;
	FriendlyNPC(Vec2, std::string);

public:
	void setUnactive();
	void setActive();

};
