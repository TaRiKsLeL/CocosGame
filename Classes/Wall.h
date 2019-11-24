#pragma once

#include "Building.h"

class Wall :public Building {
private:

public:

	Wall(bool,const vector<std::string>*);
	
	void pay(int&) override;

	int hp;
	void repair();
};