#pragma once

#include "Building.h"

class Mine : public Building {

	int amInside{0};

public:
	Mine(const vector<std::string>*);
	
	virtual PhysicsBody* createPhysBody();

	void addWorker();

	int workersAmountInside();

	void pay(int&) override;
};