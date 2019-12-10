#pragma once
#include "FriendlyNPC.h"

class Builder : public FriendlyNPC 
{
private:

	bool m_isBuilding;
	bool goToBuilding;
	Animate* animBuild;

public:
	Builder(Vec2);
	void setBuild(bool);
	bool isBuilding();
	bool isMovingToBuilding();
	void setMovingToBuild(bool);
};
