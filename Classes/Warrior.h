#pragma once
#include "FriendlyNPC.h"
#include "Shooter.h"

class Warrior : public FriendlyNPC, public Shooter, public ITimeDepended
{
private:
	//bool isFree;

public:
	Warrior(Vec2);
	virtual void timeDependedAction() override;
	virtual void removeTarget() override;
	virtual void setTarget(Node*) override;

};
