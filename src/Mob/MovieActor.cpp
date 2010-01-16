#include "MovieActor.h"
#include "..\\Management\\GameControl.h"

/**
	�W���R���X�g���N�^
*/
MovieActor::MovieActor(int rSizeX, int rSizeY)
{
	mSizeX = rSizeX;
	mSizeY = rSizeY;

	mJikiColliding = false;

  	mAnimSet = new AnimationSet();
	mSDrawer = new SimpleDrawer();				  
	mSDrawer->SetPositionInfo(this);
}

/**
	�W���f�X�g���N�^
*/
MovieActor::~MovieActor()
{
	delete mAnimSet;
	delete mSDrawer;
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void MovieActor::Move()
{
	// ��Ұ���
	mAnimSet->ElapseTime( SP->FrameTime );

	// �ړ�
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void MovieActor::Draw()
{
	// �`���ݒ肷��
	mSDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	mSDrawer->Draw();
}

/************************************************************//**
*	�W���̓����蔻��\n
*
*	�q���C��������Ώۂ���B�G�Ƒ���̓����艞���́A�G���S������B
*	
*	\param rCollObject	����������̵�޼ު��(��F�۲�)
*	\param rThisGroupId	��������GROUPID(���X�ɂ���ĈႤ)
*	\param rOpGroupId	����������̵�޼ު�Ă�GROUPID(���X�ɂ���ĈႤ)
*
****************************************************************/
void MovieActor::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO )
		mJikiColliding = true;
}


/************************************************************//**
*	\return ��Ұ��ݾ��
****************************************************************/
AnimationSet* MovieActor::GetAnimationSet()
{
	return mAnimSet;
}


/************************************************************//**
*	\return �۲݂̖��ҍU���ɓ���������
*	:UGLY:
****************************************************************/
bool MovieActor::IsJikiColliding()
{
	return mJikiColliding;
}