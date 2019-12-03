#pragma once

#include "Building.h"
#include "IAttackable.h"

class Wall :public Building , public IAttackable {
private:
	int m_HP;

public:


	Wall(Direction ,const vector<std::string>*);
	
	void pay(int&) override;

	void repair();
	void setHP(int);

	virtual PhysicsBody* createPhysBody();

	virtual bool canBeAttacked() override;
	virtual void hit(int) override;
	virtual void specitalUpdateAction() override;

};