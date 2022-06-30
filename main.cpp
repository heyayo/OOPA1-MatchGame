#include <iostream>
#include "Game.h"

bool Running = true;
short turns = 0;

int main()
{
	Init();
	Render();
	D_Render();
	while (Running)
	{
		if (!Query())
			continue;
		turns++;
		if (!Check() && turns > 1)
		{
			Close();
		}
		std::cout << Check() << std::endl;
		Render();
		D_Render();
		turns *= !(turns > 1);
	}
}