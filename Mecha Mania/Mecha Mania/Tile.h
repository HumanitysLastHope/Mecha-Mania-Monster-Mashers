#pragma once
#include "Enums.h"
#include "Mecha.h"
//#include "Bullet.h"
//#include "Mine.h"

class CTile
{
public:
	CTile();
	~CTile();

	EENVIRONMENT GetEnviroment();
	//CBullet* GetBullet();
	CMecha* GetMecha();
	//CMine* GetMine();

	//CMine* m_pMine;
	CMecha* m_pMecha;
	EENVIRONMENT m_peEnvironment;
};