#pragma once

#include "Building.h"
class Tower : public Building 
{
public:
	Tower(bool,const vector<std::string>*);

	void pay(int&) override;
};