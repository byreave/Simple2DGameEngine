#include "MonsterController.h"
#include <iostream>
int MonsterController::MonsterID = 0;
MonsterController::~MonsterController()
{
	
}

//True means that player was caught
bool MonsterController::Move(const Point2D<int>& playerPos)
{
	int distanceX = playerPos.getX() -m_Actor->GetPosition().getX();
	int distanceY = playerPos.getY() -m_Actor->GetPosition().getY();


	if (abs(distanceX) >= abs(distanceY))
	{
		if (distanceX < 0)
			m_Actor->SetPosition(m_Actor->GetPosition().getX() - 1, m_Actor->GetPosition().getY());
		else
			m_Actor->SetPosition(m_Actor->GetPosition().getX() + 1, m_Actor->GetPosition().getY());
	}
	else
	{
		if (distanceY < 0)
			m_Actor->SetPosition(m_Actor->GetPosition().getX(), m_Actor->GetPosition().getY() - 1);
		else
			m_Actor->SetPosition(m_Actor->GetPosition().getX(), m_Actor->GetPosition().getY() + 1);
	}
	std::cout << "To approach player, Monster named " << m_Actor->GetName() << " moves to [" <<m_Actor->GetPosition().getX() << ", " <<m_Actor->GetPosition().getY() << "].\n";

	if (playerPos ==m_Actor->GetPosition())
	{
		std::cout << "Monster named " << m_Actor->GetName() << "catches player at [" <<m_Actor->GetPosition().getX() << ", " <<m_Actor->GetPosition().getY() << "].\n" <<
			"However player fights valiantly and kills it, player HP - 1.\n";

		Respawn();

		std::cout << "To avenge its friend another monster named " << m_Actor->GetName() << " appears at [" <<m_Actor->GetPosition().getX() << ", " <<m_Actor->GetPosition().getY() << "].\n";
		return true;
	}
	m_Actor->SetLives(m_Actor->GetLives() - 1);
	if (m_Actor->GetLives() <= 0)
	{
		std::cout << "After 20 moves and " << m_Actor->GetName() << " exhausted and died.\n";
		Respawn();
		std::cout << "In the meanwhile a monster named " << m_Actor->GetName() << " appears at [" <<m_Actor->GetPosition().getX() << ", " <<m_Actor->GetPosition().getY() << "].\n";
	}

	return false;
}

bool MonsterController::Respawn()
{
	if (m_Actor->GetName() == NULL)
		return false;
	srand(MonsterController::MonsterID);
	const char * tmpName = m_Actor->GetName();
	int newNameLength = strlen(tmpName);
	int postfixLen = (MonsterController::MonsterID >= 26) ? 2 : 1;
	char * newName = new char[newNameLength + postfixLen];
	memcpy(newName, tmpName, newNameLength + 1);
	//currently support 26*26 monster names
	if (postfixLen == 1)
	{
		newName[strlen(tmpName) - 1] = 'A' + MonsterID;
		newName[strlen(tmpName)] = '\0';

	}
	else
	{
		newName[strlen(tmpName) - 1] = 'A'-1 + MonsterID / 26;
		newName[strlen(tmpName)] = 'A' + MonsterID % 26;
		newName[strlen(tmpName) + 1] = '\0';

	}
	MonsterController::MonsterID++;

	//for (int i = 1; i <= postfixLen; ++i)
	//{
	//	if (newName[newNameLength - i] + 1 <= 'Z')
	//	{
	//		newName[newNameLength - i] ++;
	//		break;
	//	}
	//	else
	//	{
	//		if (i == postfixLen)
	//			//Monster ID > 26 * 26
	//			return false;
	//		newName[newNameLength - i] = 'A';
	//	}
	//}
	m_Actor->SetName(newName);
	delete newName;
	m_Actor->SetPosition(rand() % 40 + 50, rand() % 101);
	m_Actor->SetLives(20);
	return true;
}
