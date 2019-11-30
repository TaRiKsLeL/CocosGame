#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Shooter {
private:

public:
	PhysicsBody* createPhysicsBody();
	void shoot();
};
