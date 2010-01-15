#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "OokamiHouse.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	������
****************************************************************/
OokamiHouse::OokamiHouse()
{
	mAppearedHeight = 0;
	mAlpha = 1.0f;
	mStatus = APPEARING;
	mPtGenerator = NULL;

	mY = GI("OOKAMI_HSPY");

	mSizeX = GI("OOKAMI_HSSX");
	mSizeY = GI("OOKAMI_HSSY");
	OOKAMI_HSSP = GF("OOKAMI_HSSP");;
}

/************************************************************//**
*	�����̵�޼ު�Ă���������
****************************************************************/
OokamiHouse::~OokamiHouse()
{
	if( mPtGenerator ) delete mPtGenerator;
}

/************************************************************//**
*	\param rX �o����X���W�ƂȂ�
*	Y�͌Œ�ł��邽�߁A�ݒ�s�\�ł�
****************************************************************/
void OokamiHouse::SetPosX(int rX)
{
	mX = rX;
}

/************************************************************//**
*	�Ƃ����ű�Ұ��݂ɓ���A�����Ă���
****************************************************************/
void OokamiHouse::Destroy()
{
	mStatus = DISAPPEARING;

	// �j�мު�ڰ����쐬
	BuildParticleGenerator();
}


/************************************************************//**
*	�n�ʂ���o�Ă���
****************************************************************/
void OokamiHouse::Appear() 
{
	if( mAppearedHeight < mSizeY ){
		mAppearedHeight += OOKAMI_HSSP;
	}
	else mAppearedHeight = mSizeY;
}

/************************************************************//**
*	���ł���
****************************************************************/
void OokamiHouse::Disappear() 
{
	// ̪��ޱ��
	mAlpha -= 0.01f;

	// �j�Д�юU�炷
	if( mPtGenerator )
		mPtGenerator->Generate();

	// ���ŏ���
	if( mAlpha < 0 ) GAMECONTROL->GetMobManager()->Remove(this);
}

/************************************************************//**
*	�j�Ђ̐�����į�߂����܂�
****************************************************************/
void OokamiHouse::StopParticles()
{
	delete mPtGenerator;
	mPtGenerator = NULL;
}

/************************************************************//**
*	
****************************************************************/
void OokamiHouse::Move() 
{
	// ����
	switch( mStatus ){
		case APPEARING: Appear(); break;
		case DISAPPEARING: Disappear(); break;
	}
	
	// �`��
	DX_DRAWALPHA(GetGraphicSrc(), mX, mY-mAppearedHeight, 0, 0, mSizeX, 
		mAppearedHeight, mAlpha);
}
