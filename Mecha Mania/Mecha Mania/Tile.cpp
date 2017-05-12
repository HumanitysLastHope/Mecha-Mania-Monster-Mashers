#include <algorithm>
#include "Tile.h"


CTile::CTile() :
	m_peEnvironment(FLOOR)
{
	
}


CTile::~CTile()
{
}

EENVIRONMENT CTile::GetEnvironment()
{
	return m_peEnvironment;
}

void  CTile::SetEnvironment(EENVIRONMENT _peEnvironment)
{
	m_peEnvironment = _peEnvironment;
}


CMecha* CTile::GetMecha() const
{
	return m_pMecha;
}

CMine* CTile::GetMine() const
{
	return m_pMine;
}

CBullet* CTile::GetBullet() const
{
	return m_vecpBullets.size() != 0 ? m_vecpBullets[0] : nullptr;
}

void CTile::SetMecha(CMecha* _pMecha)
{
	m_pMecha = _pMecha;
}

void CTile::SetMine(CMine* _pMine)
{
	m_pMine = _pMine;
}

bool CTile::RemoveBullet(const CBullet * _pBullet)
{
	// Search for the bullet to be removed
	bool bResult = false;
	auto it = std::remove(m_vecpBullets.begin(), m_vecpBullets.end(), _pBullet);
	if (it != m_vecpBullets.end())
		bResult = true;

	// Remove the bullet from the list if it is found
	if (bResult == true)
		m_vecpBullets.erase(it, m_vecpBullets.end());

	// Return whether we removed a bullet from the list or not
	return bResult;
}

void CTile::AddBullet(CBullet * _pBullet)
{
	m_vecpBullets.push_back(_pBullet);
}

int CTile::GetBulletCount() const
{
	return m_vecpBullets.size();
}
