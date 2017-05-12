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
	CMecha* GetMecha() const;
	CMine* GetMine() const;
	CBullet* GetBullet() const;
	void SetMine(CMine* _pMine);
	void SetMecha(CMecha* _pMecha);
	bool RemoveBullet(const CBullet* _pBullet);
	void AddBullet(CBullet* _pBullet);
	int GetBulletCount() const;

private:
	CMine* m_pMine;
	CMecha* m_pMecha;
	std::vector<CBullet*> m_vecpBullets;

	EENVIRONMENT m_peEnvironment;
};