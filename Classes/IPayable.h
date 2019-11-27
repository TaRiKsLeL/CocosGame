#pragma once

class IPayable {
public:
	virtual void pay(int&) {};
	virtual void onChangeFocus() {};
	virtual ~IPayable() {};
};