#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackAspire.h"
#include "ASOokamiBlowAttackFaint.h"
#include "OokamiHouseStraw.h"
#include "OokamiHouseRog.h"
#include "OokamiHouseBrick.h"
#include "Storm.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"

/************************************************************//**
*	�ʒu���̍쐬
****************************************************************/
void ASOokamiBlowAttackAspire::BuildAnimation(ActionState* rPrevState)
{
	if( !mAnimation ){
		mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackAspire.txt");
	}
}

/************************************************************//**
*	�Ƃ���
****************************************************************/
void ASOokamiBlowAttackAspire::OnEnter() 
{
	// �Ƃ���
	if( !storm ){ //�ŏ��ɌĂ΂ꂽ���̂�
		straw->Destroy();
		rog->Destroy();
	}

	// �����o��(���̂�)
	if( !storm ){
		storm = new Storm(mMuki);
		GAMECONTROL->GetMobManager()->Request(storm, true);
		// SE
		GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_bress_atack.wav");
		GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_house_break.wav");
	}
}


/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASOokamiBlowAttackAspire::Update() {
	// �I������
	return mAnimation->GetLoopCount() == 10;
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASOokamiBlowAttackAspire::OnExit() 
{
	// ���̽ï��
	mParent->AddNextAction(new ASOokamiBlowAttackFaint());
	
	// �����~�߂�
	GAMECONTROL->GetMobManager()->Remove(storm);
	storm = NULL;

	// �ݶނ̉Ƃ�߂�����
	brick->Destroy();

	// SE
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_atack.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_house_break.wav");
	

}
