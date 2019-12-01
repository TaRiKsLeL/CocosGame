#pragma once

#include "cocos2d.h"
#include "ITimeDepended.h"

USING_NS_CC;

class MoneyEarner : ITimeDepended {

	int sumToGive{ 0 };
public:
	void addWorker();
	void timeDependedAction() override;

	MoneyEarner();
	MoneyEarner(int);
};