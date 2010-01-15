#include "ChtInflictDamage.h"
#include "..\\GameControl.h"

ChtInflictDamage::ChtInflictDamage(int rKey) : Cheat( rKey )
{}

ChtInflictDamage::~ChtInflictDamage()
{}

void ChtInflictDamage::DoCheat()
{
	GAMECONTROL->GetJiki()->InflictDamage();
}