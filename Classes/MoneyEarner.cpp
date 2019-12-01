#include "MoneyEarner.h"
#include "Player.h"

void MoneyEarner::addWorker()
{
	sumToGive += COINS_PER_WORKER;
}

void MoneyEarner::timeDependedAction()
{
	Player::getInstance()->addMoney(sumToGive);
}

MoneyEarner::MoneyEarner(){}

MoneyEarner::MoneyEarner(int salaryTime)
{
	GameTime::addTimeDependedObject(salaryTime, this);
}
