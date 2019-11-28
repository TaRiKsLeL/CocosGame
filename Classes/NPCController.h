#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"
#include "Enviroment.h"

USING_NS_CC;

template <class T> class NCPController
{

private:

	vector<T*>* m_NPCs;

public:

	NPCController();
	void create(Vec2);
	void allMoveRand();
	T* findByPosition(Vec2);
	T* findClosestFree(Vec2);
};


template <typename T> NPCController<T>::NPCController() {
	m_NPCs = new std::vector<T*>();
}

template <typename T> void NPCController<T>::create(Vec2 pos) {

	m_NPC->push_back(new T(pos));
}

template <typename T> void NPCController<T>::allMoveRand() {
	for (T* tmp : *m_NPCs) {
		GameTime::addMoveableObject(tmp);
	}
}

template <typename T> T* NPCController<T>::findByPosition(Vec2 pos) {

	for (T* tmp : *m_NPCs) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}

