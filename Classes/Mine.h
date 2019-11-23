#pragma once

#include "Building.h"

class Mine : public Building {
public:
	Mine(const vector<std::string>*);

	void pay(int&) override;
};