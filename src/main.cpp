#include "GameField.h"
#include "Player.h"
#include "Enemy.h"

#include <windows.h>

void updateField(BattlePlayer& bt_player, GameField& enemyField, GameField& playerField, Enemy enemy)
{
	system("cls");

	for (auto& shootPosition : bt_player.getShootsPositions())
	{
		enemyField.setChar(shootPosition.first, shootPosition.second, 'X');
	}
	// Print all ship hits on field
	for (auto& hit : bt_player.getHitedShipsPositions())
	{
		enemyField.setChar(hit.first, hit.second, '*');
	}

	for (auto& shootPosition : enemy.getShootsPositions())
	{
		playerField.setChar(shootPosition.first, shootPosition.second, 'X');
	}

	for (auto& hit : enemy.getHitPositions())
	{
		playerField.setChar(hit.first, hit.second, '*');
	}

	std::cout << "Your field : \n";
	playerField.print();
	std::cout << "\nEnenemy field :\n";
	enemyField.print();
}


int main()
{
	srand(time(NULL));

	GameField playerField;
	GameField enemyField;

	BuilderPlayer b_player{ true };

	std::vector<std::pair<int, int>> enemyShipsPosition
	{
		{0,0},
		{2,0},
		{5,6}, {5, 7},
		{7,1},{7,2},{7,3},{7,4}
	};

	Enemy enemy{ enemyShipsPosition };

	if (b_player.getPresset()) {

		for (auto& i : b_player.getPlacedShipPositions()) {
			playerField.setChar(i.first, i.second, b_player.getPlayerChar());
		}
		playerField.print();

	}
	else {
		if (b_player.getMode())
		{
			playerField.setChar(b_player.getPosition().first, b_player.getPosition().second, b_player.getPlayerChar());
		}

		playerField.print();

		// Builder mode statements
		while (b_player.getMode()) {

			b_player.update();

			// if b_player pressed any button update game field, if not, just check for b_player inputs
			if (b_player.getMoved()) {

				//Draw all not placed ship parts
				for (auto& part : b_player.getCurrentPositions()) {
					playerField.setChar(part.first, part.second, b_player.getPlayerChar());
				}

				// Draw all placed ships
				for (auto& placed : b_player.getPlacedShipPositions()) {
					playerField.setChar(placed.first, placed.second, b_player.getPlayerChar() + 2);
				}

				playerField.print();
				b_player.toggleMoved();

				b_player.displayInfo();

				playerField.clearField();

			}

			Sleep(100);
		}
	}
	
	// Battle mod statements
	BattlePlayer bt_player{ enemy };
	updateField(bt_player, enemyField, playerField, enemy);
	bool playerTurn = true;

	while (bt_player.isInGame())
	{
		if(bt_player.getShipsCount() == 0 || enemy.getShipsCount() == 0)
		{
			bt_player.changeGameState();
		}

		if (playerTurn) {
			bt_player.update();
			playerTurn = false;
		}
		else {
			enemy.Shoot(bt_player.getShipsPositions());
			playerTurn = true;
		}
		
		
		// Print all field shoots
		updateField(bt_player, enemyField, playerField, enemy);

	}

	return 0;
}
