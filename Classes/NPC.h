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

	bool m_isMoving;
	bool stop;
	bool goingToRemove;

	float moveSpeed;

	Direction direction;

	Sprite* spr;
	Vec2 currentPointToMove;

	//Animation
	//Animate* animIdle;
	Animate* animWalk;

	NPC(Vec2);
	PhysicsBody* createPhysBody();
	
	void moveTo(Vec2);
	void resetDirection();
public:


	void setMoveSpeed(float);
	Direction getDirection();
	void setSprDirection(Direction);


	void moveStart(Vec2 pos);

	Vec2 getCurrentPointMoveTo();
	void stopMoving();

	void addChild(Sprite*);
	void removeAllChildren();
	void deleteObj();

	bool isMoving();
	bool isGoingToRemove();

	Vec2 getPosition();
	Rect getBoundingBox();

	virtual void move() override;

	virtual bool canBeAttacked() = 0;
	virtual void hit(int) = 0;
};
