#pragma once
#include "cocos2d.h"
#include "CitizenController.h"
#include <vector>

USING_NS_CC;

template <class NPC>
class  NPCController {


private:

	std::vector <NPC*> vectorNPCs;

public:

	virtual void createNPC(Vec2);

};
