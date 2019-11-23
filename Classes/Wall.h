#pragma once

#include "Building.h"

class Wall :public Building {
private:

public:

	Wall(vector<std::string>);
	Wall(bool,vector<std::string>);

	int hp;
	void repair();
};