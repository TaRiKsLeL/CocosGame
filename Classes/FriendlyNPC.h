#pragma once
#include"cocos2d.h"
#include"Data.h"
#include <ctime>
#include"IMoveable.h"

USING_NS_CC;

class FriendlyNPC : public IMoveable {

protected:

	bool isActive;
	bool isMoving;

	Sprite* spr;
	Vec2 currentPointToMove;

	Vec2 randPoint(int fromX, int toX);
	FriendlyNPC(Vec2, std::string);
	PhysicsBody* createPhysBody();

public:
	void setUnactive();
	void setActive();
	void moveTo(Vec2);
	Vec2 getPosition();
	virtual void move() override;

};
