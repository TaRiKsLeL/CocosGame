#include "GameTime.h"
#include "EnvironmentUI.h"
USING_NS_CC;



int GameTime::frameCount{ -1 };
int GameTime::currentTime{ -1 };

stack<ITimeDepended*>* GameTime::deleteTimeDependedStack = new stack<ITimeDepended*>();
stack<GameTime::MoveableToDelete*>* GameTime::deleteMoveableStack = new stack<GameTime::MoveableToDelete*>();

vector<IMoveable*> *GameTime::moveableObjects = new vector<IMoveable*>();

map<ITimeDepended*,int> *GameTime::timeDependedObjects = new map<ITimeDepended*,int>();

void GameTime::updateFrame() {
	frameCount++;

	while (deleteMoveableStack->size() > 0)
	{
		GameTime::MoveableToDelete* obj = deleteMoveableStack->top();
		deleteMoveableStack->pop();

		for (int i = 0; i < moveableObjects->size(); i++) {
			
			if ((moveableObjects->at(i)) == obj->obj) {

				moveableObjects->erase(moveableObjects->begin() + i);

				if(!obj->deleteAll)
				break;
			}
		}
	}	
	
	for (IMoveable* tmpObj : *moveableObjects) {
		tmpObj->move();
	}



	if (frameCount >= DELTA_TIME) {
		frameCount = 0;
		currentTime++;

		if (currentTime == DAY_DURATION)
			currentTime = 0;

		log("current time: %d", currentTime);


		while (deleteTimeDependedStack->size() > 0)
		{
			log("delete timeDepended obj");

			timeDependedObjects->erase(deleteTimeDependedStack->top());
			deleteTimeDependedStack->pop();
		}
	
		for each (TimeAction tmpPair in *timeDependedObjects)
		{
			if ((tmpPair.second == currentTime || tmpPair.second == -1) && tmpPair.first != nullptr)
				tmpPair.first->timeDependedAction();
		}

	}

	EnvironmentUI::getInstance()->updateBackground();
}

const int GameTime::getCurrentTime() {
	return currentTime;
}


void GameTime::addTimeDependedObject(int time, ITimeDepended* objToAdd) {
	timeDependedObjects->insert(TimeAction(objToAdd,time));
}

void GameTime::addMoveableObject(IMoveable* objToAdd) {
	moveableObjects->push_back(objToAdd);
}

void GameTime::removeTimeDependedObject(ITimeDepended* objToErase) {
	deleteTimeDependedStack->push(objToErase);
}
void GameTime::removeMoveableObject(IMoveable* objToRemove, bool deleteAll) {

	GameTime::MoveableToDelete* obj = new GameTime::MoveableToDelete(objToRemove, deleteAll);

	deleteMoveableStack->push(obj);
}