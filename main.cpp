#include <iostream>
#include "Game.h"

bool Running = true;
bool turns = false;
short pairs = 18;

int main()
{
	Init();
	Render();
	while (Running)
	{
		if (!Query())
			continue;
		Render();
		if (!Check() && turns)
		{
			Close();
		}
		turns = !turns;
		if (Check())
			pairs--;
		if (!pairs)
		{
			Win();
			Running = false;
		}
		D_Render();
	}
}
