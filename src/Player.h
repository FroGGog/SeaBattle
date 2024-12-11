#pragma once
#include <conio.h>
#include <iostream>
#include <vector>
#include <map>

#include "Enemy.h"

class Player
{
protected:

	char playerChar;

	bool moved;
public:

	Player();

	virtual void update() = 0;

	bool getMoved() const;
	char getPlayerChar() const;

	virtual const std::pair<int, int>& getPosition() = 0;

	void toggleMoved();
};

enum class SHIPTYPE {ONE, TWO, THREE, FOUR};
//This class is for start stage of game where you place your ships, build your fleet
class BuilderPlayer : public Player {

private:

	std::vector<std::pair<int, int>> partPositions;

	// vector to store all placed ships positions
	std::vector<std::pair<int, int>> builtShipPositions;
	
	// map to count all not placed ships by type
	std::map<SHIPTYPE, int> ships;

	SHIPTYPE type;

	std::pair<int, int> savedPos;

	bool rotated;
	bool inBuilderMode;
	bool preset;

	//functions
	void initShips();

	// add ship parts based on ship type
	void addPartsPos(int repeat);

	void switchType(int partsNum);
	//check if we can transform to bigger ship
	bool checkValidSwitchType(int partsToAdd);

	// Place and save ship
	void placeShip();
	bool checkValidPlace();

	// Delete ship
	void deleteShip();

	// Rotate ship
	void rotateShip();
	bool checkValidRotate(std::pair<int,int>& position);

public:

	BuilderPlayer();
	BuilderPlayer(bool done);

	void update() override;
	void displayInfo();

	const std::vector<std::pair<int, int>>& getCurrentPositions();
	const std::vector<std::pair<int, int>>& getPlacedShipPositions();
	const std::pair<int, int>& getPosition() override;
	const bool getMode() const;
	const bool getPresset() const;

};

class BattlePlayer : public Player
{
private:

	std::vector <std::pair<int, int>> shootsPositions;
	std::vector <std::pair<int, int>> shipsPositions;
	std::vector <std::pair<int, int>> hitedShipsPoisitions;

	std::pair<int, int> currentPosition;

	bool inGame;
	int enemyShipsCount; 

	void doShoot(std::pair<int, int> shootPosition);


public:
	BattlePlayer(Enemy& enemy);
	
	void update() override;

	const std::vector<std::pair<int, int>>& getHitedShipsPositions();
	const std::vector<std::pair<int, int>>& getShootsPositions();
	const std::vector<std::pair<int, int>>& getShipsPositions();
	const std::pair<int, int>& getPosition() override;
	const bool isInGame() const;
	const int getShipsCount() const;

	void changeGameState();

};