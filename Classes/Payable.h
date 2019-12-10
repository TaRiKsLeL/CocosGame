#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Payable {
private:
	Sprite* selector;

protected:
	
	void setSelectorSpr(Sprite*);
	Payable();
public:
	virtual void pay(int&) {};
	virtual void setSelector() = 0;
	virtual void onChangeFocus() {};
	virtual void removeSelector();
};