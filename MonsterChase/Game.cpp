#include<iostream>
#include<stdlib.h> //random
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG
#include <Windows.h>//Heap
#include "Monster.h"
#include "Player.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "Vector.h"
#include "ConsoleLog.h"
#include "HeapManagerProxy.h"


extern bool HeapManager_UnitTest();
void * operator new(size_t i_size, HeapManager * pHeapManager)
{
	DEBUG_PRINT("MSG", "CALLED NEW NEW!");
	if (pHeapManager != nullptr)
	{
		return HeapManagerProxy::alloc(pHeapManager, i_size);
	}
	return nullptr;
}

void operator delete(void * ptr, HeapManager * pHeapManager)
{
	DEBUG_PRINT("MSG", "CALLED NEW DELETE!");

	if (pHeapManager != nullptr)
	{
		HeapManagerProxy::free(pHeapManager, ptr);
	}
}
using namespace std;
int main()
{
	using namespace HeapManagerProxy;
	//Allocation test
	//bool test = HeapManager_UnitTest();
	
	//variables
	int gridWidth = 100, gridHeight = 100;
	int monNumber = 0;//number of monsters
	char move;
	Monster * mon;
	MonsterController * monCon;
	MonsterController::SetIDZero();
	Vector<Monster *> * monVec;
	Vector<MonsterController *> * monConVec;
	char playerName[128], monName[128];
	//Create Heap
	const size_t 		sizeHeap = 1024 * 1024;
	const unsigned int 	numDescriptors = 2048;

	// Allocate memory for my test heap.
	void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);
	assert(pHeapMemory);

	// Create a heap manager for my test heap.
	HeapManager * pHeapManager = CreateHeapManager(pHeapMemory, sizeHeap, numDescriptors);
	assert(pHeapManager);

	if (pHeapManager == nullptr)
		return false;
	//startup
	srand(123);
	cout << "Enter number of monsters to start: \n";
	cin >> monNumber;
	cout << "Enter the name of monster:\n";
	cin >> monName;

	assert(monName != "");
	cout << "Enter Player's Name\n";
	cin >> playerName;
	assert(playerName != "");

	//intialize player
	Player *player = new (pHeapManager) Player(playerName);
	player->SetPosition(rand() % 51, rand() % 101);
	PlayerController * playerCon = new PlayerController();
	playerCon->SetActor(player);
	

	cout<<"Player "<<player->GetName()<<" enters the arena at [" << player->GetPosition().getX() << ", " << player->GetPosition().getY() << "].\n";
	//create monsters
	monVec = new Vector<Monster *>();
	monConVec = new Vector<MonsterController *>();
	for (int i = 0; i < monNumber; i ++)
	{
		monCon = new MonsterController();
		mon = new Monster(monName, i);
		monCon->SetActor(mon);
		monCon->SetTarget(player);
		DEBUG_PRINT("Event", "Generated a monster named %s", mon->GetName());
		monVec->push(mon);
		monConVec->push(monCon);
	}
	mon = nullptr;
	//mon = new Monster[monNumber];
	//for (int i = 0; i < monNumber;)
	//{
	//	mon[i].respawn(monName, i);
	//	cout << i << endl;
	//	std::cout << "To catch player, Monster named " << mon[i - 1].Name << " appears at [" << mon[i - 1].Pos.getX() << ", " << mon[i - 1].Pos.getY() << "].\n";
	//}

	cout << "OK, Battle begins.\n" <<
		"Use WASD to move, Q to quit, try to live as long as you can!\n";
	for (;;)
	{
		cout << "--------------------------------------\n" <<
			"Make your move: \n";
		cin >> move;
		if (move == 'Q' || move == 'q')
			break;
		else if (move != 'W' && move != 'S' && move != 'A' && move != 'D' && move != 'w' && move != 'a' && move != 's' && move != 'd')
		{
			cout << "Use WASD or wasd to move, Q or q to quit, try to live as long as you can!\n";
			continue;
		}
		else
		{
			playerCon->SetMove(move);
			playerCon->UpdateActor();
			//suicide
			for (int i = 0; i < monNumber; ++i)
			{
				if (player->GetPosition() == (*monVec)[i]->GetPosition())
				{
					cout << playerName << "'s head hit right on a monster named " << (*monVec)[i]->GetName() << ".\n";
					if (player->ReduceHP())
					{
						cout << playerName << "'s head is so hard that " << (*monVec)[i]->GetName() << " ends up dead.\n";
						(*monConVec)[i]->Respawn();
						DEBUG_PRINT("Event", "A monster named %s repawned.", (*monVec)[i]->GetName());

						cout << "However, to avenge its friend another monster named " << (*monVec)[i]->GetName() << " appears at[" << (*monVec)[i]->GetPosition().getX() << ", " << (*monVec)[i]->GetPosition().getY() << "].\n";
					}
					break;
				}
			}
			for (int i = 0; i < monNumber; ++i)
			{
				(*monConVec)[i]->UpdateActor();
			}
			if (player->GetLives() <= 0)
			{
				cout << playerName << " Suffered an unfortunate fate and died.\n";
				break;
			}
		}
	}

	std::cout << "Game Over.\n";
	player->~Player();
	::operator delete(player, pHeapManager);
	//delete player;
	delete playerCon;
	//monVec->clear();
	delete monVec;
	delete monConVec;
	//Destroy Heap
	Destroy(pHeapManager);
	pHeapManager = nullptr;

	HeapFree(GetProcessHeap(), 0, pHeapMemory);
#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif // DEBUG
	return 0;
}