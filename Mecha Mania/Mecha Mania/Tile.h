#pragma once
#include "Enums.h"
#include "Mecha.h"
#include "Bullet.h"
#include "Mine.h"

class CTile
{
public:
	CTile();
	~CTile();

	EENVIRONMENT GetEnvironment();
	void SetEnvironment(EENVIRONMENT _peEnvironment);
	CMecha* GetMecha();
	CMine* GetMine();
	CBullet* GetBullet();
	void SetMine(CMine* _pMine);
	void SetMecha(CMecha* _pMecha);
	void SetBullet(CBullet* _pBullet);

private:
	CMine* m_pMine;
	CMecha* m_pMecha;
	CBullet* m_pBullet;

	EENVIRONMENT m_peEnvironment;
};