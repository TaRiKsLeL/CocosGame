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

	Sprite* spr;
	Vec2 currentPointToMove;

	NPC(Vec2, std::string);
	PhysicsBody* createPhysBody();
	void moveTo(Vec2);

public:

	void setMoveSpeed(float);

	void moveStart(Vec2 pos);

	Vec2 getCurrentPointMoveTo();
	void stopMoving();


	void addChild(Sprite*);
	void removeAllChildren();
	void deleteObj();

	Vec2 getPosition();

	virtual void move() override;
	virtual void hit(int) override;
};
