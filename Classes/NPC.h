#pragma once
#include"cocos2d.h"
#include "Data.h"
#include "GameTime.h"
#include "IMoveable.h"
#include "IAttackable.h"

USING_NS_CC;

class NPC : public IMoveable , public IAttackable
{

protected:

	bool isMoving;
	bool stop;

	float moveSpeed;

	Direction direction;

	Sprite* spr;
	Vec2 currentPointToMove;

	NPC(Vec2, std::string);
	PhysicsBody* createPhysBody();

	void moveTo(Vec2);
	void resetDirection();

public:

	void setMoveSpeed(float);
	Direction getDirection();

	void moveStart(Vec2 pos);

	Vec2 getCurrentPointMoveTo();
	void stopMoving();

	void addChild(Sprite*);
	void removeAllChildren();
	void deleteObj();

	Vec2 getPosition();
	Rect getBoundingBox();

	virtual void move() override;

	virtual bool canBeAttacked() = 0;
	virtual void hit(int) = 0;
};
