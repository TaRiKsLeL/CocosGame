#pragma once

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class AnimationCreator 
{
	static AnimationCreator* animationCreator;

	//AnimationCreator();

public:

	static AnimationCreator* getInstance();

	Animate* createAnimate(string, int, int, int, float);
};