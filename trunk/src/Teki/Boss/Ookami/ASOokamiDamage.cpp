#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiDamage.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"

/************************************************************//**
*	±ÆÒ°¼®Ý‚Ìì¬
****************************************************************/
void ASOokamiDamage::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\Damage.txt" );
}

/************************************************************//**
*	@see ActionState
****************************************************************/
void ASOokamiDamage::OnEnter()
{
	mMutekiJikan->Start();
}

/************************************************************//**
*	’¼iˆÚ“®‚ÆI—¹ðŒ
****************************************************************/
bool ASOokamiDamage::Update() 
{
	//Ë¯ÄÊÞ¯¸
	// I—¹ðŒ
	return (mAnimation->GetLoopCount() == 2);
}

void ASOokamiDamage::OnExit() 
{}

