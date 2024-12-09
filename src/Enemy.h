#pragma once
#include <vector>

class Enemy 
{
private:
	std::vector<std::pair<int, int>> placedShipsPositions;
	std::vector<std::pair<int, int>> shootedPostions;
	std::vector<std::pair<int, int>> hitedPositions;

public:

	Enemy(std::vector<std::pair<int, int>>& shipPositions);

	void Shoot(const std::vector<std::pair<int, int>>& playerShipsPostions);
	
	const std::vector<std::pair<int, int>>& getPlacedShipsPositions();
	const std::vector<std::pair<int, int>>& getShootsPositions();
	const std::vector<std::pair<int, int>>& getHitPositions();

};