#pragma once

class IAttackable 
{
public:
	virtual void hit(int) = 0;
	virtual bool canBeAttacked() = 0;
};
