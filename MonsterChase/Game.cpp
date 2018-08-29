#include<iostream>
#include<stdlib.h>
#include "Monster.h"
#include "Player.h"


using namespace std;
int main()
{
	//variables
	int gridWidth = 100, gridHeight = 100;
	int monNumber = 0;//number of monsters
	int monCount = 0; //For naming
	char move;
	Monster * mon;
	string playerName, monName;

	//startup
	cout << "Enter number of monsters to start: \n";
	cin >> monNumber;
	cout << "Enter the name of monster:\n";
	cin >> monName;
	cout << "Enter Player's Name\n";
	cin >> playerName;
	monCount = monNumber;
	//intialize player
	Player player;
	player.Pos.x = rand() % 51;
	player.Pos.y = rand() % 101;

	cout<<"Player enters the arena at [" << player.Pos.x << ", " << player.Pos.y << "].\n";
	//create monsters
	mon = new Monster[monNumber];
	for (int i = 0; i < monNumber;)
	{
		mon[i].respawn(monName, i);
		cout << i << endl;
		std::cout << "To catch player, Monster named " << mon[i-1].Name << " appears at [" << mon[i-1].Pos.x << ", " << mon[i-1].Pos.y << "].\n";
	}

	cout << "OK, Battle begins.\n" <<
		"Use WASD to move, Q to quit, try to live as long as you can!\n";
	for (;;)
	{
		cout << "--------------------------------------\n" <<
			"Make your move: \n";
		cin >> move;
		if (move == 'Q' || move == 'q')
			break;
		else if (move != 'W' && move != 'S' && move != 'A' && move != 'D')
		{
			cout << "Use WASD (not wasd) to move, Q to quit, try to live as long as you can!\n";
			continue;
		}
		else
		{
			player.Move(move);
			//suicide
			for (int i = 0; i < monNumber; ++i)
			{
				if (player.Pos == mon[i].Pos)
				{
					cout << playerName << "'s head hit right on a monster named " << mon[i].Name << ".\n";
					if (--player.Lives > 0)
					{
						cout << playerName << "'s head is so hard that " << mon[i].Name << " ends up dead.\n";
						mon[i].respawn(monName, monCount);
						cout << "However, to avenge its friend another monster named " << mon[i].Name << " appears at[" << mon[i].Pos.x << ", " << mon[i].Pos.y << "].\n";
					}
					break;
				}
			}
			for (int i = 0; i < monNumber; ++i)
			{
				mon[i].Move(player.Pos, monCount, monName);
			}
			if (player.Lives <= 0)
			{
				cout << playerName << " Suffered an unfortunate fate and died.\n";
				break;
			}
		}
	}

	std::cout << "Game Over.\n";
	return 0;
}