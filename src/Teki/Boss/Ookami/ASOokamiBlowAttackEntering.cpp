#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackEntering.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "ASOokamiBlowAttackInspire.h"

/************************************************************//**
*	�ʒu���̍쐬
****************************************************************/
void ASOokamiBlowAttackEntering::BuildPosInfo(ActionState* rPrevState)
{
	// �Œ���
	ASOokamiStraightAttack::BuildPosInfo(rPrevState);
	
	// X���x
	mSpX = (mMuki?1:-1) * GI("OOKAMI_ENTERSPX");
}

/************************************************************//**
*	OnEnter
****************************************************************/
void ASOokamiBlowAttackEntering::OnEnter() {
	// SE
	GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_move.wav");
}

/************************************************************//**
*	��ʂɓ����ďI���
****************************************************************/
bool ASOokamiBlowAttackEntering::Update() {
	// ���i
	mX += mSpX;

	// �I������
	return ((mMuki && mX > OOKAMI_ENTERLX) || (!mMuki && mX < OOKAMI_ENTERRX));
}

/************************************************************//**
*	���̽ðĂɈڂ�
****************************************************************/
void ASOokamiBlowAttackEntering::OnExit() 
{
	mParent->AddNextAction(new ASOokamiBlowAttackInspire());
}
