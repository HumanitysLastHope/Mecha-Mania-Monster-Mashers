#include "Mine.h"
#include "Board.h"



CMine::CMine(CBoard* _pBoard, TPosition _posGridPosition):
CMovable(_pBoard, _posGridPosition)
{
}


CMine::~CMine()
{
}

TPosition CMine::getPosition()
{
	return m_posGridPosition;
}

void CMine::ArmMine()
{
	m_isArmed = true;
}

bool CMine::isArmed()
{
	return m_isArmed;
}

bool CMine::Move(EDIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case WEST:
		// Checks if you would hit a wall
		if (m_posGridPosition.m_iX == 0)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha() != nullptr) //PUSHED ONTO PLAYER WITH MINE UNDERNEATH
		{

			m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha()->ChangeHealth(-2);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr); // set tile to null
			bombBlown();

			return false;

		}
		// If there's a mine in front move that mine
		if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMine() != nullptr)
		{

			if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMine()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).SetMine(this);
		m_posGridPosition.m_iX--;
		break;

	case NORTH:
		if (m_posGridPosition.m_iY == 0)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY -1).GetMecha() != nullptr) //PUSHED ONTO PLAYER WITH MINE UNDERNEATH
		{

			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY -1).GetMecha()->ChangeHealth(-2);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr); // set tile to null
			bombBlown();

			return false;

		}

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMine() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMine()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).SetMine(this);
		m_posGridPosition.m_iY--;
		break;

	case EAST:
		if (m_posGridPosition.m_iX == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha() != nullptr) //PUSHED ONTO PLAYER WITH MINE UNDERNEATH
		{

			m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha()->ChangeHealth(-2);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr); // set tile to null
			bombBlown();

			return false;

		}

		if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMine() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMine()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).SetMine(this);
		m_posGridPosition.m_iX++;
		break;

	case SOUTH:
		if (m_posGridPosition.m_iY == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha() != nullptr) //PUSHED ONTO PLAYER WITH MINE UNDERNEATH
		{
			
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha()->ChangeHealth(-2);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr); // set tile to null
			bombBlown();

			return false;

		}
		else if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMine() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMine()->Move(_eDirection) == false)
			{
				return false;
			}
		}
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).SetMine(this);
		m_posGridPosition.m_iY++;
		break;

	default:
		break;
	}
	return true;
}

void CMine::bombBlown()
{
	delete this;
}