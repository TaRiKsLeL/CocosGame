#pragma once

class IMoveable {
public:
	virtual void move() = 0;
};


struct MoveDirection
{
	bool left{ false };
	bool right{ false };
};
