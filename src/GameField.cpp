#include "GameField.h"
#include <algorithm>
#include <iostream>

GameField::GameField()
{
	m_gameField = std::vector<std::vector<std::string>>(8,std::vector<std::string>(8, " "));
}

void GameField::setChar(int x, int y, unsigned char z)
{
	m_gameField[x][y] = z;
}

void GameField::print()
{

	std::cout << " ";
	char start = 'A';
	char startNum = '1';

	// start with printing first line with letters
	for (int letters{ 0 }; letters < 8; letters++) {
		std::cout << start;
		start++;
	}
	// print all nums in one collumns
	std::cout << '\n';
	for (int nums{ 0 }; nums < 8; nums++) {
		std::cout << startNum;
		for (auto i : m_gameField[nums]) {
			std::cout << i;
		}
		startNum++;
		std::cout << "\n";
	}

}

void GameField::clearField()
{
	std::for_each(m_gameField.begin(), m_gameField.end(), [](std::vector<std::string>& vec)
		{
			for (auto& i : vec)
			{
				i = ' ';
			}
		}
	);
}

