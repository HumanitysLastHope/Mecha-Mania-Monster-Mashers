#pragma once

#include <vector>

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
	bool RemoveBullet(CBullet* _pBullet);
	void AddBullet(CBullet* _pBullet);

private:
	CMine* m_pMine;
	CMecha* m_pMecha;
	std::vector<CBullet*> m_vecpBullets;

	EENVIRONMENT m_peEnvironment;
};