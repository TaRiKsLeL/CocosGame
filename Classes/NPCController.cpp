#include "NPCController.h"

template <typename T> 
NPCController<T>::NPCController() {
	m_NPCs = new std::vector<T*>();
}

template <class T> 
void NPCController<T>::create(Vec2 pos) {

	m_NPC->push_back(new T(pos));
}

template <class T> 
void NPCController<T>::allMoveRand() {
	for (T* tmp : *m_NPCs) {
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

