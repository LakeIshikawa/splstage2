#include "ChtNoDamage.h"
#include "..\\GameControl.h"

ChtNoDamage::ChtNoDamage(int rKey) : Cheat( rKey )
{}

ChtNoDamage::~ChtNoDamage()
{}

void ChtNoDamage::DoCheat()
{
	GAMECONTROL->GetJiki()->ToggleNoDamageMode();
}