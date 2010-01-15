#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASWaitForMaku.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Animation\\Animation.h"

/************************************************************//**
*	�����蔻��Ȃ�
****************************************************************/
void ASWaitForMaku::BuildCollision(ActionState* rPrevState) 
{
	mCollision = NULL;
}

/************************************************************//**
*	ϯ�߂����蔻��Ȃ�
****************************************************************/
void ASWaitForMaku::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ϯ�߂����蔻��Ȃ�
}

/************************************************************//**
*	��Ұ��݂��p��
****************************************************************/
void ASWaitForMaku::BuildAnimation(ActionState* rPrevState) 
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
void ASWaitForMaku::BuildMobDrawer(ActionState* rPrevState) 
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
void ASWaitForMaku::BuildOtherInfo(ActionState* rPrevState) 
{}

/************************************************************//**
*	�����蔻��̉����Ȃ�
****************************************************************/
void ASWaitForMaku::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnEnter() 
{
	
}

/************************************************************//**
*	�����オ���Ă���̂�҂�
****************************************************************/
bool ASWaitForMaku::Update() {
	if( mOpenClose )
		return GAMECONTROL->GetMaku()->IsClosed();
	else
		return GAMECONTROL->GetMaku()->IsOpen();
}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnExit() {
	
}
