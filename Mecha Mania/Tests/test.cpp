#include <conio.h>

#include <GameEngine.h>
#include <MovingBulletsState.h>
#include <Position.h>
#include <Enums.h>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* argv[])
{
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...

	_getch();

	return (result < 0xff ? result : 0xff);
}

TEST_CASE("Test Bullet Movement")
{
	// Init game engine
	CGameEngine gameEngine;

	// Add some bullets
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 2, 0 }, EDIRECTION::SOUTH);
	CBullet* pBullet3 = gameEngine.SpawnBullet({ 2, 2 }, EDIRECTION::WEST);
	CBullet* pBullet4 = gameEngine.SpawnBullet({ 0, 2 }, EDIRECTION::NORTH);

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();
	// Check 'one' bullet moves appropriately
	REQUIRE(pBullet1->GetPosition().m_iX == 1);
	REQUIRE(pBullet1->GetPosition().m_iY == 0);
	REQUIRE(gameEngine.GetBoard().GetTile(1, 0).GetBullet() == pBullet1);

	// Run one step
	gameEngine.Step();
	// Check 'one' bullet moves appropriately
	REQUIRE(pBullet2->GetPosition().m_iX == 2);
	REQUIRE(pBullet2->GetPosition().m_iY == 1);
	REQUIRE(gameEngine.GetBoard().GetTile(2, 1).GetBullet() == pBullet2);

	// Run one step
	gameEngine.Step();
	// Check 'one' bullet moves appropriately
	REQUIRE(pBullet3->GetPosition().m_iX == 1);
	REQUIRE(pBullet3->GetPosition().m_iY == 2);
	REQUIRE(gameEngine.GetBoard().GetTile(1, 2).GetBullet() == pBullet3);
	// Run one step
	gameEngine.Step();
	// Check 'one' bullet moves appropriately
	REQUIRE(pBullet4->GetPosition().m_iX == 0);
	REQUIRE(pBullet4->GetPosition().m_iY == 1);
	REQUIRE(gameEngine.GetBoard().GetTile(0, 1).GetBullet() == pBullet4);
}

TEST_CASE("Test spawning bullet ontop of existing bullet")
{
	// Init game engine
	CGameEngine gameEngine;

	// Add some bullets
	gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::SOUTH);

	// Check that both bullets are destroyed
	REQUIRE(gameEngine.GetBulletList().empty());
	REQUIRE(gameEngine.GetBoard().GetTile(0, 0).GetBullet() == nullptr);
}

TEST_CASE("Test bullets colliding")
{
	// Init game engine
	CGameEngine gameEngine;

	std::vector<CBullet*>& rvecpBullets = gameEngine.GetBulletList();
	CBoard& rBoard = gameEngine.GetBoard();

	// Add some bullets
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 1, 0 }, EDIRECTION::WEST);

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();
	// Check both bullets collide and are destroyed
	auto it1 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet1);
	auto it2 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet2);
	REQUIRE(it1 == rvecpBullets.end());
	REQUIRE(it2 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(0, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(1, 0).GetBullet() == nullptr);
}