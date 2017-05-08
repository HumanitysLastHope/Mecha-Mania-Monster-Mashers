#pragma once
#include "Enums.h"
#include "Mecha.h"
//#include "Bullet.h"
#include "Mine.h"

class CTile
{
public:
	CTile();
	~CTile();

	EENVIRONMENT GetEnvironment();
	void SetEnvironment(EENVIRONMENT _peEnvironment);
	//CBullet* GetBullet();
	CMecha* GetMecha();
	CMine* GetMine();
	void SetMine(CMine* _pMine);
	void SetMecha(CMecha* _pMecha);
	//CMine* GetMine();

private:
	CMine* m_pMine;
	CMecha* m_pMecha;

	EENVIRONMENT m_peEnvironment;
};