#pragma once
#include "FriendlyNPC.h"
#include "Shooter.h"

class Warrior : public FriendlyNPC, public Shooter, public ITimeDepended
{
private:
	bool inTower;

public:
	Warrior(Vec2);
	virtual void timeDependedAction() override;
	virtual void removeTarget() override;
	virtual void setTarget(Node*) override;
	void setSprite(string);
	void setFixedPosition(Vec2);
	bool isOnTower();

};
