#pragma once

#include "Building.h"

class Mine : public Building {
public:
	Mine(const vector<std::string>*);
	
	virtual PhysicsBody* createPhysBody();

	void pay(int&) override;
};