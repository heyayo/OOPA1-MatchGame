#include <iostream>
#include <random>
#include <string>
#include "Game.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

char board[6][6];
char boardvalue[6][6];
int memory[2][2];
bool match = false;
int total = 0;
int arow;
unsigned int intSeed = 0;
std::string seed;
#ifdef _WIN32
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

// Function to return a random number between the MIN and MAX ints specified, exclusive of the MAX
float RandRange(float MIN, float MAX)
{
	return (((float)rand() / (float)RAND_MAX) * (MAX-MIN)) + MIN;
}

void SeedQuery()
{
	std::cout << "Enter a Seed for the game" << std::endl;
	std::getline(std::cin,seed);
	for (int i = 0; i < seed.length(); i++)
	{
		intSeed += (int)seed[i];
	}
}

// Initializes the game
void Init()
{
	// Seeds the randomizer used in the game
	srand(intSeed);

	// Initializes the board array as empties
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			board[i][j] = ' ';
		}
	}

	// Initializes the Memory Array that remembers the user's selection as different negative numbers
	// Different Negatives are required as to not throw off the Check Function
	for (int i = 0; i < 2; i++)
	{
		memory[0][i] = -1;
		memory[1][i] = -2;
	}

	// Temporary Array to store the 18 different alphabet pairs
	char boxes[18];
	// Temporary Array that mirrors the 'boxes' array as it generates to ensure that the randomizer does not pick same letter pairs
	char mem[18];
	// For Loop that generates random letter pairs and stores them into the 'boxes' array
	// If a letter is found in the 'mem' array, the for loop's incrementer will be decremented to repeat the random process for that pair
	for (int i = 0; i < 18; i++)
	{
		short count = 0; // Counts how many times a letter has appeared
		char slot = (char)RandRange(97, 122); // Generates a number from 97 (a) to 122 (z) and casts it to a char to get the letter pair
		boxes[i] = slot; // Stores the Generated pair into the 'boxes' array
		mem[i] = slot; // Stores the Generated pair into the 'memory' array
		// Check if the pair generated has generated before
		for (int j = 0; j < 18; j++)
		{
			count += (boxes[i] == mem[j]); // If letter has generated before, increment count
		}
		i -= (count > 1); // If letter has generated twice, decrement for loop
	}

	// Distributes the letter pairs across the board
	for (int i = 0; i < 18; i++)
	{
		// Find a pair of spots for each letter
		for (int j = 0; j < 2; j++)
		{
			// Generate a random place
			int row = (int)RandRange(0, 6);
			int col = (int)RandRange(0, 6);
			// If the spot is taken, regenerate
			if (boardvalue[row][col])
			{
				j--;
				continue;
			}
			// If spot not taken, the spot is given to the letter
			boardvalue[row][col] = boxes[i];
		}
	}

	// Reset The Global Memory Array and Arrow Coordinates
	arow = -1;
	ResetMemory();
}

// This function Renders the board
void Render()
{
	// Clears the Console
	#ifdef _WIN32
	// WINDOWS Implementation
	system("cls");
	#elif __linux__
	// Linux Implementation
	system("clear");
	#endif

	for (int i = 0; i < 6; i++)
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;

	// Renders the top bar of the board UI
	for (int j = 0; j < 15; j++)
	{
		std::cout << '_';
	}
	std::cout << std::endl;
	
	// Renders the rest of the board UI
	for (int i = 0; i < 6; i++)
	{
		#ifdef _WIN32
		SetConsoleTextAttribute(console, 9);
		std::cout << j;
		SetConsoleTextAttribute(console, 15);
		#elif __linux__
		std::cout << "\033[34m" << i << "\033[0m";
		#endif

		// The Pillar on the left
		std::cout << '|';

		// The Contents of the board with the pillars between
		for (int j = 0; j < 6; j++)
		{
			// Colors the Text According to which opened first
			#ifdef _WIN32 // WINDOWS Implementation
			if (memory[0][0] == i && memory[0][1] == j)
			{
				SetConsoleTextAttribute(console, 10);
				std::cout << board[i][j];
				SetConsoleTextAttribute(console, 15);
			}
			else if (memory[1][0] == i && memory[1][1] == j)
			{
				SetConsoleTextAttribute(console, 11);
				std::cout << board[i][j];
				SetConsoleTextAttribute(console, 15);
			}
			else
			{
				std::cout << board[i][j];
			}
			#elif __linux__ // Linux Implementation
			if (memory[0][0] == i && memory[0][1] == j)
			{
				std::cout << "\033[32m" << board[i][j] << "\033[0m";
			}
			else if (memory[1][0] == i && memory[1][1] == j)
			{
				std::cout << "\033[36m" << board[i][j] << "\033[0m";
			}
			else
			{
				std::cout << board[i][j];
			}
			#endif
			std::cout << '|';
		}
		// The arrow that reminds the player which row they selected
		if (i == arow)
		{
			std::cout << " <";
		}
		std::cout << std::endl;

		// The splitting horizontal line of the board
		for (int j = 0; j < 15; j++)
		{
			std::cout << '_';
		}
		std::cout << std::endl;
	}
}

// The Debug Version of the Render without any "Pretty" UI that also gives the answers
// Uncomment if you want to cheat
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

// "Opens" a card
void Open(int row, int col)
{
	board[row][col] = boardvalue[row][col]; // Reveals the card value
	memory[match][0] = row; // Remember the card's row
	memory[match][1] = col; // Remembers the card's column
	match = !match; // Switch the turn card, the next turn will be the one to match
	total++; // Increment the total amount of turns
}

// Ask the player for input
bool Query()
{
	int row, col; // Temporary variables to store the row and column variable
	std::cout << "Which Row?" << std::endl; // Ask which row
	std::cin >> row; // Get Row
	arow = row - 1; // Save Arrow Position
	Render(); // Render Mid Question to Render Arrow
	std::cout << "Which Column?" << std::endl; // Ask which column
	std::cin >> col; // Get Column
	arow = -1; // Reset arrow Position
	// If the board position does not exist or is open, tell player
	if (board[row - 1][col - 1] != ' ')
	{
		std::cout << "Card Already Open" << std::endl;
		return false; // Tell the main loop that the player's selection is bad
	}
	// Open card
	Open(row - 1, col - 1);
	return true; // Tell the main loop that the player has picked a good pair
}

// Check if both cards picked are the same
bool Check()
{
	return (boardvalue[memory[0][0]][memory[0][1]] == boardvalue[memory[1][0]][memory[1][1]]);
}

// Close both cards and forgets about them
void Close()
{
	board[memory[0][0]][memory[0][1]] = ' ';
	board[memory[1][0]][memory[1][1]] = ' ';
	ResetMemory();
}

// Forget the selected card values
void ResetMemory()
{
	memory[0][0] = -1; memory[0][1] = -1;
	memory[1][0] = -2; memory[1][1] = -2;
}

// Tell the player they won
// This is a function despite being used once as it needs to access the 'total' variable
void Win()
{
	std::cout << "You Win and Took a Total of " << total / 2 << " Turns to Finish" << std::endl;
	std::cout << "This Game was played with the Seed [" << seed << ']' << std::endl;
#ifdef _WIN32
	system("pause");
#endif
}

