#pragma once

#include "cocos2d.h"
#include <vector>
#include "IPayable.h"
#include "FriendlyNPC.h"

USING_NS_CC;

class Citizen :public FriendlyNPC, public IPayable {
private:
	bool isPayed;
public:
	Citizen(Vec2);

	virtual void pay(int&) override;
	virtual void onChangeFocus() override;

};

