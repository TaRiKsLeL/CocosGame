#pragma once
#include "IAttackable.h"
#include "Building.h"
#include "GameOverScene.h"

class Castle : public Building , public IAttackable {

public:
	Castle(const vector<std::string>*);

	void pay(int&) override;
	
	virtual PhysicsBody* createPhysBody();

	virtual void specitalUpdateAction() override;
	virtual bool canBeAttacked() override;
	virtual void hit(int) override;
};