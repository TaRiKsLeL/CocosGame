#pragma once

#include "Building.h"

class Wall :public Building {
private:

public:
	int hp;
	void repair();
};