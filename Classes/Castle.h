#pragma once

#include "Building.h"
class Castle : public Building {

public:
	Castle(const vector<std::string>*);

	void pay(int&) override;

};