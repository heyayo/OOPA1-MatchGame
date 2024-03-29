#include <iostream>
#include "Game.hpp"
#include "timer.hpp"

//#define _DEBUGV_ // Uncomment to Enable Cheat Features

// Basic Variables needed to run the game
bool Running = true; // Says game is running
bool turns = false; // Saves which card is being opened, the one to match or the first one
short pairs = 18; // The amount of pairs needed to match

int main()
{
	#ifdef _DEBUGV_
	std::cout << "This compile has DEBUG enabled" << std::endl << "You are required to match " << pairs << " pairs to win" << std::endl;
	#endif
	std::cout << "Please Full Screen Your Terminal For The Best Experience" << std::endl;
	std::cout << "F11 or Maximize Button" << std::endl;
	StopWatch timer;
	timer.startTimer();
	timer.waitUntil(2000);
	SeedQuery(); // Ask User for Game Seed
	Init(); // Intialize Game
	ClearScreen();
	Render(); // Perform the first render of the game
	while (Running) // Game Loop
	{
		if (!Query()) // Query the player on the card to open
			continue; // If the Query returns false, restart loop
		ClearScreen();
		Render();// Render if success
		if (!Check() && turns) // Check if both cards are the same and if two cards have been opened
		{
			std::cout << "Mismatch! Try Again" << std::endl;
			Close(); // Close the cards
		}
		turns = !turns; // Flip the turn
		if (Check()) // If both cards are the same, decrease the pair variable to count for win
		{
			std::cout << "Matched!" << std::endl;
			pairs--;
			ResetMemory();
		}
		if (!pairs) // If all pairs matched, win game
		{
			Win(); // Win Game
			Running = false; // Stop Game
		}
		#ifdef _DEBUGV_
		D_Render(); // DEBUG RENDER, cheat/debug purpose
		#endif
	}
}
