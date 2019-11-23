#include "GameTime.h"
USING_NS_CC;

int GameTime::frameCount{ 0 };

stack<ITimeDepended*>* GameTime::deleteStack = new stack<ITimeDepended*>();

vector<IMoveable*> *GameTime::moveableObjects = new vector<IMoveable*>();

map<ITimeDepended*,int> *GameTime::timeDependedObjects = new map<ITimeDepended*,int>();

void GameTime::updateFrame() {
	frameCount++;

	for (IMoveable* tmpObj : *moveableObjects) {
		tmpObj->move();
	}

	if (frameCount >= DELTA_TIME) {
		frameCount = 0;
		if(timeDependedObjects->size()>0)
			for each (TimeAction tmpPair in *timeDependedObjects)
			{
				tmpPair.first->timeDependedAction();
				log("In loop of dependent objects");
			}
		while (deleteStack->size() > 0) 
		{
			timeDependedObjects->erase(deleteStack->top());
			deleteStack->pop();
		}
	}
}

void GameTime::addTimeDependedObject(int time, ITimeDepended* objToAdd) {
	timeDependedObjects->insert(TimeAction(objToAdd,time));
}

void GameTime::addMoveableObject(IMoveable* objToAdd) {
	moveableObjects->push_back(objToAdd);
}

void GameTime::removeTimeDependedObject(ITimeDepended* objToErase) {
	log("In erace");
	deleteStack->push(objToErase);
}
void GameTime::removeMoveableObject(IMoveable* objToRemove) {

}