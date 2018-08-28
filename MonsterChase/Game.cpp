#include<iostream>
#include "Monster.h"
#include "Player.h"


using namespace std;
int main()
{
	//variables
	int monNumber = 0;//number of monsters
	Monster * mon;
	string playerName, monName;

	//startup
	cout << "Enter number of monsters to start: \n";
	cin >> monNumber;
	cout << "Enter the name of monster:\n";
	cin >> monName;
	cout << "Enter Player's Name\n";
	cin >> playerName;

	//create monsters
	mon = new Monster[monNumber];
	for (int i = 0; i < monNumber - 1; ++i)
	{
		
	}

	std::cout << "asdf";
	return 0;
}