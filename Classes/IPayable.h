#pragma once

class IPayable {
public:
	virtual void pay(int &) = 0;
};