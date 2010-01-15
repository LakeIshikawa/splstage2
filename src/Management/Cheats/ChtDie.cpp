#include "ChtDie.h"
#include "..\\GameControl.h"

ChtDie::ChtDie(int rKey) : Cheat( rKey )
{}

ChtDie::~ChtDie()
{}

void ChtDie::DoCheat()
{
	GAMECONTROL->GetJiki()->Die();
}