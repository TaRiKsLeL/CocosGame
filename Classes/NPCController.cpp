#include "NPCController.h"

template <class T> 
NPCController<NPC>::NPCController() {
	m_NPCs = new std::vector<NPC*>();
}

template <class T> 
void NPCController<NPC>::create(Vec2 pos) {

	m_NPC->push_back(new NPC(pos));
}

template <class T> 
void NPCController<NPC>::allMoveRand() {
	for (NPC* tmp : *m_NPCs) {
		GameTime::addMoveableObject(tmp);
	}
}

template <class T> 
T* NPCController<T>::findByPosition(Vec2 pos) {

	for (T* tmp : *m_NPCs) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}

template <class T> 
T* NPCController<T>::findClosestFree(Vec2 pos) {

	for (NPC* tmp : *m_NPCs) {
		if (tmp->getPosition().x == pos.x)
			return tmp;
	}

	return nullptr;
}