#include <iostream>
#include "Game.hpp"

// Basic Variables needed to run the game
bool Running = true; // Says game is running
bool turns = false; // Saves which card is being opened, the one to match or the first one
short pairs = 18; // The amount of pairs needed to match

int main()
{
	SeedQuery(); // Ask User for Game Seed
	Init(); // Intialize Game
	Render(); // Perform the first render of the game
	while (Running) // Game Loop
	{
		if (!Query()) // Query the player on the card to open
			continue; // If the Query returns false, restart loop
		Render();// Render if success
		if (!Check() && turns) // Check if both cards are the same and if two cards have been opened
		{
			Close(); // Close the cards
		}
		turns = !turns; // Flip the turn
		if (Check()) // If both cards are the same, decrease the pair variable to count for win
		{
			pairs--;
			ResetMemory();
		}
		if (!pairs) // If all pairs matched, win game
		{
			Win(); // Win Game
			Running = false; // Stop Game
		}
		D_Render(); // DEBUG RENDER, cheat/debug purpose
	}
}
