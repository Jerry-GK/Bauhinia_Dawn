#include <iostream>
#include "game.h"
#include "game_map.h"
#include "player.h"
#include "vehicle.h"
#include "zombie.h"
#include "weapon.h"

using namespace std;

int main()
{
	Game g;
	g.Init();
	while(!g.is_end())
	{
		g.read();
	}
	g.quit();
	system("pause");
	return 0;
}
