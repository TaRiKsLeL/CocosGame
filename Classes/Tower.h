#pragma once

#include "Building.h"
class Tower : public Building 
{
public:
	Tower(vector<std::string>);
	Tower(bool,vector<std::string>);
};