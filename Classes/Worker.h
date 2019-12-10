#pragma once
#include "FriendlyNPC.h"

class Worker : public FriendlyNPC
{
public:
	Worker(Vec2);
	Sprite* getSprite();
};
