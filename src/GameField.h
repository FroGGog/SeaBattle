#pragma once
#include <vector>
#include <string>

class GameField
{
private:

	std::vector <std::vector<std::string>> m_gameField;

public:

	GameField();

	void setChar(int x, int y, unsigned char z);

	void print();

	void clearField();

};

