#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"

USING_NS_CC;

template <class T> class NCPController
{

private:

	vector<NPC*>* m_NPCs;

public:

	NPCController();
	void create(Vec2);
	void allMoveRand();
	T* findByPosition(Vec2);
	T* findClosestFree(Vec2);
};
