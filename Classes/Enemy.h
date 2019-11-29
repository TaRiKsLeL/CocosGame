#pragma once
#include "NPC.h"

class Enemy : public NPC 
{
private:

	int attPower;
	int HP;
	
	Action* createJmp();

public:

	Enemy(Vec2);

	int getAttPower();
	void jmpBack();
	
	virtual bool canBeAttacked() override;
	virtual void hit(int) override;
};
