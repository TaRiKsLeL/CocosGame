#pragma once
#include "cocos2d.h"
#include <vector>
#include "Data.h"

USING_NS_CC;
using namespace std;

template <typename T> class BaseController
{

private:

	std::vector<T*> *m_NPCs;

public:

	BaseController() {
		m_NPCs = new vector<T*>();
	};

	void create(Vec2 pos) {
		m_NPCs->push_back(new T(pos));
	};

	void allMoveRand() {
		for (T* tmp : *m_NPCs) {
			tmp->moveRandStart();
		}
	};
	
	void allStopMove() {
		for (T* tmp : *m_NPCs) {
			tmp->stopMoving();
		}
	};
	
	T* deleteByPos(Vec2 pos) {
		T* toDelete = findByPosition(pos);


		for (int i = 0; i < m_NPCs->size(); i++) {
			if (m_NPCs->at(i)->getPosition().x == pos.x) {
				m_NPCs->erase(m_NPCs->begin() + i);
				break;
			}
		}

		toDelete->deleteObj();

		return toDelete;

	};

	T* findByPosition(Vec2 pos) {

		for (T* tmp : *m_NPCs) {
			if (tmp->getPosition().x == pos.x)
				return tmp;
		}

		return nullptr;
	};

	vector<T*>* getElems() {
		return m_NPCs;
	}
};

