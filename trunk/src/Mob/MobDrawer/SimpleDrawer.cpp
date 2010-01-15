#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "SimpleDrawer.h"
#include "..\\..\\Animation\\Animation.h"
#include "..\\IPositionable.h"
#include "..\\..\\Management\\GameControl.h"


/************************************************************//**
*	������
****************************************************************/
SimpleDrawer::SimpleDrawer() : 
mAnimation(NULL), mPositionInfo(NULL), mAlphaCapable(NULL)
{}


/************************************************************//**
*	�W���̕`��
****************************************************************/
void SimpleDrawer::Draw() 
{
	// ���݂��ڰєԍ��̎擾
	int frno = mAnimation->GetCurFrameIdx();

	// �`��
	DX_SCROLL_ROT_DRAWALPHA( mAnimation->GetGraphicSource(), 
		mPositionInfo->GetX(), mPositionInfo->GetY(), 
		frno*mPositionInfo->GetFrameSizeX(), 
		mPositionInfo->GetMuki()*mPositionInfo->GetFrameSizeY(),
		(frno+1)*mPositionInfo->GetFrameSizeX(), 
		(mPositionInfo->GetMuki()+1)*mPositionInfo->GetFrameSizeY(), 0.0f,
		mAlphaCapable ? mAlphaCapable->GetAlpha() : 1.0f);
}

/************************************************************//**
*	���̵�޼ު�Ă̸۰݂����o��
****************************************************************/
MobDrawer* SimpleDrawer::Clone() 
{
	SimpleDrawer* newobj = new SimpleDrawer();
	newobj->mAnimation = mAnimation;
	newobj->mPositionInfo = mPositionInfo;
	newobj->mAlphaCapable = mAlphaCapable;

	return newobj;
}

/************************************************************//**
*	\param rAnimation ��Ұ��ݵ�޼ު��
*	�����҂͐e�ƂȂ�
****************************************************************/
void SimpleDrawer::SetAnimation(Animation* rAnimation) 
{
	mAnimation = rAnimation;
}

/************************************************************//**
*	\param rPositionInfo �ʒu����޼ު��
*	�����҂͐e�ƂȂ�
****************************************************************/
void SimpleDrawer::SetPositionInfo(IPositionable* rPositionInfo) 
{
	mPositionInfo = rPositionInfo;
}

/************************************************************//**
*	\param rAlphaCapable ��̧��޼ު��
****************************************************************/
void SimpleDrawer::SetAlphaSrc(IAlphaCapable* rAlphaCapable) 
{
	mAlphaCapable = rAlphaCapable;
}
