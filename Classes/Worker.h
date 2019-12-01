#pragma once
#include "FriendlyNPC.h"

class Worker : public FriendlyNPC
{private:
	bool isMovingToMine;

public:
	Worker(Vec2);
	void setMovingToMine(bool);
	bool movingToMine();
};
