#pragma once

#include "Enums.h"

class CMovable
{
	CMovable();
	virtual ~CMovable();

	virtual bool Move(EDIRECTION);
};