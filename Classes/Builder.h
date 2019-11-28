#pragma once
#include "IPayable.h"
#include "FriendlyNPC.h"

class Builder : public FriendlyNPC 
{
private:
	bool m_isBuilding;

public:
	Builder(Vec2);
	void setBuild(bool);
	bool isBuilding();
};
