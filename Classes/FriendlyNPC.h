#pragma once
#include"IPayable.h"
#include "NPC.h"

USING_NS_CC;

class FriendlyNPC : public NPC , public IPayable 
{

protected:

	bool isActive;
	bool isMovingRand;
	FriendlyNPC(Vec2, string);
public:

	void setUnactive();
	void setActive();

	void moveRandStart();
	void moveStart(Vec2 pos);

	Vec2 getCurrentPointMoveTo();
	void stopMoving();
	
	virtual void move() override;

	virtual void pay(int&) override;

	virtual bool canBeAttacked() override;
	virtual void hit(int) override;
};
