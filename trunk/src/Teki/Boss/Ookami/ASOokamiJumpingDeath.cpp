#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASOokamiJumpingDeath.h"

/************************************************************//**
*	��Ұ���
****************************************************************/
void ASOokamiJumpingDeath::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\Death.txt" );
}

/************************************************************//**
*	�j�Ђ̍쐬�ƕ����~�߂�
****************************************************************/
void ASOokamiJumpingDeath::OnEnter() 
{
	// ��
	if( storm ) {
		GAMECONTROL->GetMobManager()->Remove(storm);
		storm = NULL;
	}

	// ��
	/*if( brick ) {
		brick->Destroy();
	}*/
	if( straw ) straw->StopParticles();
	if( rog ) straw->StopParticles();

	// ��{����
	ASJumpingDeath::OnEnter();

	// SE
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_atack.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_out.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_tame.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_move.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_house_break.wav");

	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_teki_down.wav");

}
