#include "Enemy.h"

Enemy::Enemy(std::vector<std::pair<int, int>>& shipPositions)
{
	placedShipsPositions = shipPositions;
    enemyShipsCount = 20;
}

void Enemy::Shoot(const std::vector<std::pair<int, int>>& playerShipsPostions)
{
    std::pair<int, int> shootPosition{ rand() % 8, rand() % 8 };

    // Try to find if already shoot in this position
    auto it = std::find(shootedPostions.begin(), shootedPostions.end(), shootPosition);

    if (it != shootedPostions.end())
    {
        return Shoot(playerShipsPostions);
    }

    // Then try shoot
    auto p_shoot = std::find(playerShipsPostions.begin(), playerShipsPostions.end(), shootPosition);

    // So if enemy missed
    if (p_shoot == playerShipsPostions.end()) {
        shootedPostions.push_back(shootPosition);
    }
    // If enemy hit enemy ship
    else {
        shootedPostions.push_back(shootPosition);
        hitedPositions.push_back(shootPosition);
        enemyShipsCount--;
    }

}

const std::vector<std::pair<int, int>>& Enemy::getPlacedShipsPositions()
{
	return placedShipsPositions;
}

const std::vector<std::pair<int, int>>& Enemy::getShootsPositions()
{
    return shootedPostions;
}

const std::vector<std::pair<int, int>>& Enemy::getHitPositions()
{
    return hitedPositions;
}

const int Enemy::getShipsCount() const
{
    return enemyShipsCount;
}
