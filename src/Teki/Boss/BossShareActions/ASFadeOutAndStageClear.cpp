#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASFadeOutAndStageClear.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Event\\StageClearEvt.h"

/************************************************************//**
*	�����蔻��Ȃ�
****************************************************************/
void ASFadeOutAndStageClear::BuildCollision(ActionState* rPrevState) 
{
	mCollision = NULL;
}

/************************************************************//**
*	ϯ�߂����蔻��Ȃ�
****************************************************************/
void ASFadeOutAndStageClear::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ϯ�߂����蔻��Ȃ�
}

/************************************************************//**
*	��Ұ��݂��p��
****************************************************************/
void ASFadeOutAndStageClear::BuildAnimation(ActionState* rPrevState) 
{
	// �����ðĂ̏ꍇ
	if( !rPrevState ){
		mAnimation = NULL;
	}

	// ����ȊO�̏ꍇ
	else{
		mAnimation = rPrevState->GetAnimation()->Clone();
	}
}

/************************************************************//**
*	�`����@���߰����
****************************************************************/
void ASFadeOutAndStageClear::BuildMobDrawer(ActionState* rPrevState) 
{
	// �����ðĂ̏ꍇ
	if( !rPrevState ){
		mMobDrawer = NULL;
	}

	// ����ȊO�̏ꍇ
	else {
		mMobDrawer = rPrevState->GetMobDrawer()->Clone();
		((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	}
}

/************************************************************//**
*	����������ނȂ�
****************************************************************/
void ASFadeOutAndStageClear::BuildOtherInfo(ActionState* rPrevState) 
{}

/************************************************************//**
*	�����蔻��̉����Ȃ�
****************************************************************/
void ASFadeOutAndStageClear::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{}

/************************************************************//**
*	
****************************************************************/
void ASFadeOutAndStageClear::OnEnter() 
{
	GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(
					TxtGraphicController::CENTER, 
					GI("STGCLRMOJI_SX"),GI("STGCLRMOJI_SY"), 
					"graphics\\txtgraphic\\stage_clear_01.png",
					GF("STGCLMOJI_DTIME"), GF("STGCLMOJI_FSP"));
}

/************************************************************//**
*	̪��ނ��s���A̪��ނ��I���̂�҂�
****************************************************************/
bool ASFadeOutAndStageClear::Update() 
{
	// �ð�޸ر�̕�����\�����Ă���̪��ޱ��
	if( GAMECONTROL->GetTxtGraphicController()->IsFinished() )
		return GAMECONTROL->GetFader()->FadeOut();

	return false;
}

/************************************************************//**
*	�ð�޸ر���Ă�
****************************************************************/
void ASFadeOutAndStageClear::OnExit() 
{
	GAMECONTROL->GetEventManager()->Request( new StageClearEvt() );
}
