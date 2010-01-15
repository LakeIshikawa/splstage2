#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ActionState.h"
#include "ActionControllable.h"
#include "..\..\MapCollision\\MapCollider.h"
#include "..\\..\\Animation\\Animation.h"

/************************************************************//**
*	�߲����̏�����
****************************************************************/
ActionState::ActionState() 
{
	mCollision = NULL;		//�����蔻��
	mMapCollider = NULL;	//ϯ�߂����蔻��
	mAnimation = NULL;		//��Ұ���
	mMobDrawer = NULL;		//�`����@

	mWasInterrupted = false; //���f���ꂽ�����׸ނ̏�����
}


/************************************************************//**
*	�����̵�޼ު�Ă��J������
****************************************************************/
ActionState::~ActionState() 
{
	if( mCollision )	delete mCollision;		//�����蔻��
	if( mMapCollider)	delete mMapCollider;	//ϯ�߂����蔻��
	if( mAnimation )	delete mAnimation;		//��Ұ���
	if( mMobDrawer )	delete mMobDrawer;		//�`����@
}


/************************************************************//**
*	��Ұ��ݎ��Ԃ��o�߂����郉�b�v�B
****************************************************************/
void ActionState::ElapseTime(float rElapsedTime) 
{
	if( mAnimation ){
		mAnimation->ElapseTime( rElapsedTime );
	}
}

/************************************************************//**
*	\param state �O��ð�
*	\param rParent ���̱���݂̐e�ƂȂ��޼ު��
*	�ðĂ��ް������o��
****************************************************************/
void ActionState::BuildState(ActionState* state, ActionControllable* rParent) 
{
	// �e�̐ݒ�
	mParent = rParent;

	// �����蔻��
	BuildCollision( state );
	// ϯ�߂����蔻��
	BuildMapCollider( state );
	// ��Ұ���
	BuildAnimation( state );
	// �`��
	BuildMobDrawer( state );
	// �h���׽�̓��ʏ��
	BuildOtherInfo( state );
	// �ʒu���
	BuildPosInfo( state );
}

/************************************************************//**
*	\param rX �z�uX
*	\param rY �z�uY
*	\param rParent ���̱���݂̐e�ƂȂ��޼ު��
*	�����ðĂƂ��č��o��
****************************************************************/
void ActionState::BuildState(int rX, int rY, ActionControllable* rParent) 
{
	
	// �e�̐ݒ�
	mParent = rParent;
	
	// �����蔻��
	BuildCollision( NULL );
	// ϯ�߂����蔻��
	BuildMapCollider( NULL );
	// ��Ұ���
	BuildAnimation( NULL );
	// �`��
	BuildMobDrawer( NULL );
	// �h���׽�̓��ʏ��
	BuildOtherInfo( NULL );
	// �ʒu���
	BuildPosInfo(rX, rY);
}


/************************************************************//**
*	\param state �O��ð�
*	�W���Ƃ��đO��ðĂ���ʒu��񂪺�߰�����
****************************************************************/
void ActionState::BuildPosInfo(ActionState* state) 
{
	mX			= state->GetX();
	mY			= state->GetY();
	mSpX		= state->GetSpX();
	mSpY		= state->GetSpY();
	mAccX		= state->GetAccX();
	mAccY		= state->GetAccY();
	mMuki		= state->GetMuki();
	mFrameSizeX	= state->GetFrameSizeX();
	mFrameSizeY	= state->GetFrameSizeY();
}

/************************************************************//**
*	\param rX �z�uX
*	\param rY �z�uY
****************************************************************/
void ActionState::BuildPosInfo(int rX, int rY) 
{
	mX			= rX;
	mY			= rY;
	mSpX		= 0;
	mSpY		= 0;
	mAccX		= 0;
	mAccY		= 0;
	mMuki		= 0;
	mFrameSizeX = 0;
	mFrameSizeY = 0;
}
