#include "GameEngine.h"
#include "GameState.h"
#include "GettingPlayerMovesState.h"
#include "ExecutingCMDState.h"
#include "Mine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

CGameEngine::CGameEngine() :
	m_Player1({0,0}, NORTH, &m_Level, 1),
	m_Player2({ 0,0 }, NORTH, &m_Level, 2),
	m_Player3({ 0,0 }, NORTH, &m_Level, 3),
	m_Player4({ 0,0 }, NORTH, &m_Level, 4)
{
	LoadBoard(1);

	m_CommandOrder.push_back(0);
	m_CommandOrder.push_back(1);
	m_CommandOrder.push_back(2);
	m_CommandOrder.push_back(3);

	ChangeState(new CGettingPlayerMovesState);
}


CGameEngine::~CGameEngine()
{
	delete m_pCurGameState;
	for (auto it = m_vecpBulletList.begin(); it != m_vecpBulletList.end(); ++it)
	{
		delete (*it);
	}
}

void CGameEngine::Step()
{
	m_pCurGameState->Step(this);

	BulletCollisionTest();

	if (m_bBulletsToDestroy)
	{
		ActuallyDestroyBullets();
	}
}

bool CGameEngine::PitCheck()
{
	bool _bReturn = false;
	//cycles through the whole grid for each tile and checks and excutes behaviour if a Mecha is standing on water, pit
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			////checks water
			//if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER && m_Level.GetTile(_iX, _iY).GetMecha() != nullptr && bWaterCheck == true)
			//{
   //				m_Level.GetTile(_iX, _iY).GetMecha()->ChangeHealth(-1);
			//	std::cout << m_Level.GetTile(_iX, _iY).GetMecha()->m_iHealth;

			//	_bReturn = true;

			//}
			//checks pit
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT && m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				m_Level.GetTile(_iX, _iY).GetMecha()->ChangeHealth(-5);
				m_Level.GetTile(_iX, _iY).SetMecha(nullptr);


				//delete m_Level.GetTile(_iX, _iY).GetMecha();
				_bReturn = true;
			}
		}
	}
	return _bReturn;
}

void CGameEngine::WaterCheck(CPlayer* _pPlayer)
{
	if (m_Level.GetTile(_pPlayer->GetMecha()->GetGridPosition().m_iX, _pPlayer->GetMecha()->GetGridPosition().m_iY).GetEnvironment() == WATER)
	{
 		_pPlayer->GetMecha()->ChangeHealth(-1);
		std::cout << _pPlayer->GetMecha()->GetHealth();

	}
}

void CGameEngine::Draw()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 128);
	//draws the arena
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			int _ibackgroundcolour;
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER) {
				_ibackgroundcolour = 144;
			}
			else {
				_ibackgroundcolour = 128;
			}
			//draw an empty tile
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == FLOOR && m_Level.GetTile(_iX, _iY).GetMecha() == nullptr && m_Level.GetTile(_iX, _iY).GetMine() == nullptr)
			{
				char _cEmptyTile = 176;
				std::cout << _cEmptyTile;
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << " ";
			}
			//draw mecha
			if (m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 1)
				{
					SetConsoleTextAttribute(hConsole, (_ibackgroundcolour + 13));
				}
				else if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 2)
				{
					SetConsoleTextAttribute(hConsole, (_ibackgroundcolour + 14));
				}
				else if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 3)
				{
					SetConsoleTextAttribute(hConsole, (_ibackgroundcolour + 10));
				}
				else
				{
					SetConsoleTextAttribute(hConsole, (_ibackgroundcolour + 11));
				}

				char _cMechaImage;
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == NORTH)
				{
					 _cMechaImage = 30;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == EAST)
				{
					 _cMechaImage = 16;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == SOUTH)
				{
					 _cMechaImage = 31;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == WEST)
				{
					_cMechaImage = 17;
				}
				std::cout << _cMechaImage;
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << " ";
				SetConsoleTextAttribute(hConsole, 128);
			}

			////draw bullet
			else if (m_Level.GetTile(_iX, _iY).GetBullet() != nullptr)
			{
				char _cBulletImage = 249;
				std::cout << _cBulletImage;
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << " ";
			}
			//draw mine
			else if (m_Level.GetTile(_iX, _iY).GetMine() != nullptr)
			{
				char _cMineImage = 15;
				SetConsoleTextAttribute(hConsole, _ibackgroundcolour + 12);
				std::cout << _cMineImage;
				m_Level.GetTile(_iX, _iY).GetMine()->ArmMine();
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << " ";
			}

			////draw water
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER)
			{
				char _cWaterImage = 126;
				SetConsoleTextAttribute(hConsole, 159);
				std::cout << _cWaterImage;
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << " ";
			}
			////draw pit
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT)
			{
				char _cPitImage = 220;
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << _cPitImage;
				std::cout << " ";
			}
			SetConsoleTextAttribute(hConsole, 128);
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
	//m_pCurGameState->Step(this);
}

void CGameEngine::ChangeState(IGameState* _pState)
{
	if (m_pCurGameState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		m_pCurGameState->Cleanup();
		delete m_pCurGameState;
	}

	m_pCurGameState = _pState;

	if (_pState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		_pState->Init();
	}
}

CBoard& CGameEngine::LoadBoard(int _LevelNum) {

	//m_PlayerList[1]

	if (_LevelNum == 1) {
		//sets the players starting locations and facing direction
		/*m_PlayerList[0].GetMecha()->SetGridPosition({ 1, 2 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(SOUTH);*/
		m_PlayerList[0].GetMecha()->SetGridPosition({ 1, 2 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(SOUTH);

		m_PlayerList[1].GetMecha()->SetGridPosition({ 2, 8 });
		m_PlayerList[1].GetMecha()->SetMechaFacingDirect(EAST);

		m_PlayerList[2].GetMecha()->SetGridPosition({ 7, 1 });
		m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);

		m_PlayerList[3].GetMecha()->SetGridPosition({ 8, 7 });
		m_PlayerList[3].GetMecha()->SetMechaFacingDirect(NORTH);

		//include code here load level 1 from txt file
		std::ifstream levelOneFile;

		levelOneFile.open("LevelOne.txt");
		if (levelOneFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}

		int j = 0;

		for (std::string line; getline(levelOneFile, line); j++)
		{
			for (int i = 0; i < 10; i++)
			{
				switch (line[i])
				{
				case 'p':
				{
					m_Level.GetTile(i, j).SetEnvironment(PIT);
					break;
				}
				case '0':
				{
					break;
				}
				case 'w':
				{
					m_Level.GetTile(i, j).SetEnvironment(WATER);

					break;
				}
				default:
				{
					break;
				}
				}
			}
		}

		//levelOneFile.open("\Mecha - Mania - Monster - Mashers\Mecha Mania\Levels\LevelOne.txt");

		return m_Level;
	}
	if (_LevelNum == 2) {
		//sets the players starting locations and facing direction


		//include code here load level 2 from txt file

		return m_Level;
	}
	if (_LevelNum == 3) {
		//sets the players starting locations and facing direction


		//include code here load level 3 from txt file

		return m_Level;
	}
	else {
		//sets the players starting locations and facing direction


		//include code here load level 4 from txt file

		return m_Level;
	}
}

CBoard & CGameEngine::GetBoard()
{
	return m_Level;
}


std::vector<CPlayer>& CGameEngine::GetPlayerList()
{
	return m_PlayerList;
}

std::vector<CBullet*>& CGameEngine::GetBulletList()
{
	return m_vecpBulletList;
}

void CGameEngine::Run()
{
	CGameEngine gameEngine;

	while (true)
	{
		gameEngine.Draw();
		gameEngine.Step();
		system("CLS");
	}

	_getch();

}

void CGameEngine::SetNewFirstPlayer()
{
	int iTemp = m_CommandOrder.front();

	m_CommandOrder.erase(m_CommandOrder.begin());
	m_CommandOrder.push_back(iTemp);
}

bool CGameEngine::BulletCollisionTest()
{
	bool bCollision = false;

	// Do bullet-bullet and bullet-mecha collision check
	for (auto it = m_vecpBulletList.begin(); it != m_vecpBulletList.end(); ++it)
	{
		CBullet* pBullet = *it;
		CTile& rTile = GetBoard().GetTile(pBullet->GetPosition());

		if (rTile.GetBulletCount() > 1)
		{
			bCollision = true;
			DestroyBullet(pBullet);
		}

		if (rTile.GetMecha() != nullptr)
		{
			bCollision = true;
			DestroyBullet(pBullet);
			rTile.GetMecha()->ChangeHealth(-pBullet->GetDamage());
		}
	}

	return bCollision;
}

CBullet* CGameEngine::SpawnBullet(const TPosition& _posBoardPos, EDIRECTION _eMovingDir)
{
	// Check we are spawning at a valid position
	if (!m_Level.IsValidPos(_posBoardPos))
	{
		return nullptr;
	}
	else
	{
		// Check if the tile already has a bullet on it (both bullets should get destroyed in this case)
		CTile& tile = m_Level.GetTile(_posBoardPos);
		if (tile.GetBullet() != nullptr)
		{
			DestroyBullet(tile.GetBullet());

			return nullptr;
		}
		else
		{
			// Create the bullet at the end of the bullet list
			m_vecpBulletList.push_back(new CBullet(&m_Level, *this, _posBoardPos, _eMovingDir));

			// Add the bullet to the board at the correct location
			CBullet* pBullet = m_vecpBulletList.back();
			tile.AddBullet(pBullet);

			return pBullet;
		}
	}
}

void CGameEngine::DestroyBullet(CBullet * pBullet)
{
	// Set game engine state to destroy bullets at a later date
	m_bBulletsToDestroy = true;

	// Set bullets state to destroyed, game engine will do actual cleanup later
	pBullet->SetDestroyed();
}

void CGameEngine::ActuallyDestroyBullets()
{
	// Conditionally remove bullets, on the condition that they are in a destroyed state
	m_vecpBulletList.erase(std::remove_if(
		m_vecpBulletList.begin(), m_vecpBulletList.end(),
		[&](const CBullet* pBullet)
	{
		if (pBullet->IsDestroyed())
		{
			// Remove from board
			m_Level.GetTile(pBullet->GetPosition()).RemoveBullet(pBullet);

			// Delete memory
			delete pBullet;

			// Tell erase function to remove from list
			return true;
		}
		else
		{
			return false;
		}
	}
	), m_vecpBulletList.end());

	m_bBulletsToDestroy = false;
}
