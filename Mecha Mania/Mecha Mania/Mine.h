#include "Position.h"
#pragma once

class Mine
{
public:
	Mine();
	~Mine();
	TPosition getPosition();

private:
	bool isArmed;
	TPosition gridPosition;

};

