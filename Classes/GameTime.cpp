#include "GameTime.h"
USING_NS_CC;

int GameTime::frameCount{ 0 };

stack<ITimeDepended*>* GameTime::deleteTimeDependedStack = new stack<ITimeDepended*>();
stack<IMoveable*>* GameTime::deleteMoveableStack = new stack<IMoveable*>();

vector<IMoveable*> *GameTime::moveableObjects = new vector<IMoveable*>();

map<ITimeDepended*,int> *GameTime::timeDependedObjects = new map<ITimeDepended*,int>();

void GameTime::updateFrame() {
	frameCount++;

	while (deleteMoveableStack->size() > 0)
	{
		for (int i = 0; i < moveableObjects->size(); i++) {
			if ((moveableObjects->at(i)) == deleteMoveableStack->top()) {

				moveableObjects->erase(moveableObjects->begin() + i);

				deleteMoveableStack->pop();

				if (deleteMoveableStack->size() == 0)
					break;
			}
		}
	}	
	
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

		while (deleteTimeDependedStack->size() > 0) 
		{
			timeDependedObjects->erase(deleteTimeDependedStack->top());
			deleteTimeDependedStack->pop();
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
	deleteTimeDependedStack->push(objToErase);
}
void GameTime::removeMoveableObject(IMoveable* objToRemove) {
	deleteMoveableStack->push(objToRemove);
}