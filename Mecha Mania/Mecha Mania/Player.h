#include "Enums.h"
#include "Mecha.h"
#include <vector>

#pragma once

class Player
{
public:
	CMecha mecha;
	std::vector<ECOMMANDS> moveList;
private:
	int m_iD;
	bool m_bisAlive;
};

