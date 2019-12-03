#pragma once

class ITimeDepended {
public:
	virtual void timeDependedAction()=0;
	virtual ~ITimeDepended() {};

};