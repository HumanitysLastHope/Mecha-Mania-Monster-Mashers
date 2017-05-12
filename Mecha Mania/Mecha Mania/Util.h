#pragma once

#include "Enums.h"

struct TPosition;

namespace Util
{
	TPosition GetNextPosition(const TPosition& _rkpos, EDIRECTION _eDirection);
	
}