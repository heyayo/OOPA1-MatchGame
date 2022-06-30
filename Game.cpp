#include <iostream>
#include <random>
#include "Game.h"

char board[6][6];
char boardvalue[6][6];
int memory[2][2];
bool match = false;

// Function to return a random number between the MIN and MAX ints specified, exclusive of the MAX
int RandRange(int MIN, int MAX)
{
	return (((float)rand() / RAND_MAX) * (MAX-MIN)) + MIN;
}

void Init()
{
	srand(2);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < 2; i++)
	{
		memory[i][0] = -1;
		memory[i][1] = -1;
	}
	char boxes[18];

	{
		char memory[18];
		for (int i = 0; i < 18; i++)
		{
			short count = 0;
			char slot = (char)RandRange(97, 122);
			boxes[i] = slot;
			memory[i] = slot;
			for (int j = 0; j < 18; j++)
			{
				count += (boxes[i] == memory[j]);
			}
			i -= (count > 1);
		}
	}

	short count;
	short memory[6];
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int row = RandRange(0, 6);
			int col = RandRange(0, 6);
			if (boardvalue[row][col])
			{
				j--;
				continue;
			}
			boardvalue[row][col] = boxes[i];
		}
	}
	ResetMemory();
}

void Render()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
}

void D_Render()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << boardvalue[i][j];
		}
		std::cout << std::endl;
	}
}

void Open(int row, int col)
{
	board[row][col] = boardvalue[row][col];
	memory[match][0] = row;
	memory[match][1] = col;
	match = !match;
}

bool Query()
{
	int row, col;
	std::cout << "Which Row?" << std::endl;
	std::cin >> row;
	std::cout << "Which Column?" << std::endl;
	std::cin >> col;
	if (board[row][col] != ' ')
	{
		std::cout << "Card Already Open" << std::endl;
		return false;
	}
	Open(row, col);
	return true;
}

bool Check()
{
	std::cout << boardvalue[memory[0][0]][memory[0][1]] << boardvalue[memory[1][0]][memory[1][1]] << std::endl;
	return (boardvalue[memory[0][0]][memory[0][1]] == boardvalue[memory[1][0]][memory[1][1]]);
}

void Close()
{
	board[memory[0][0]][memory[0][1]] = ' ';
	board[memory[1][0]][memory[1][1]] = ' ';
	ResetMemory();
}

void ResetMemory()
{
	memory[0][0] = -1; memory[0][1] = -1;
	memory[1][0] = -2; memory[1][1] = -2;
}
