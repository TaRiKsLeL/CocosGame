#pragma once
#include"cocos2d.h"
#include"Data.h"
#include <ctime>
#include"IMoveable.h"
#include"IPayable.h"

USING_NS_CC;

class FriendlyNPC : public IMoveable , public IPayable 
{

protected:

	bool isActive;
	bool isMoving;

	bool stop;
	Sprite* spr;
	Vec2 currentPointToMove;

	Vec2 randPoint(int fromX, int toX);
	FriendlyNPC(Vec2, std::string);
	PhysicsBody* createPhysBody();

public:

	void setUnactive();
	void setActive();

	void moveStart();
	void moveTo(Vec2);
	void stopMoving();
	
	Sprite* getSpr();

	Vec2 getPosition();
	
	virtual void move() override;

};
