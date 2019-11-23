#pragma once

class IPayable {
public:
	virtual void pay(int &) = 0;
	virtual void onChangeFocus() {};
	virtual ~IPayable() {};
};