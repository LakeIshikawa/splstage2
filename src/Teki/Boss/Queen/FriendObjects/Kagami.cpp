#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Kagami.h"
#include "Hibi.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
Kagami::Kagami()
{
	// �ݒ�萔
	mX = GI("KAGAMIX");
	mY = GI("KAGAMIY");
	mSizeX = GI("KAGAMISX");
	mSizeY = GI("KAGAMISY");
	KAGAMI_NIJISP = GF("KAGAMI_NIJISP");

	// (�)���
	mHibi = new Hibi(this);
	GAMECONTROL->GetMobManager()->Request(mHibi, true);
	
	// ������
	SetToColor(Color(1.0f, 1.0f, 1.0f));
	mStatus = STOP;
	mZ = -0.5f;
	mVibrator = new Vibrator(3, 1.0f, 1.0f);
}

/************************************************************//**
*�@�����̵�޼ު�Ă��J������
****************************************************************/
Kagami::~Kagami()
{
	if( mVibrator ) delete mVibrator;
}

/************************************************************//**
*	��Ұ��݂ƕ`����s��
****************************************************************/
void Kagami::Move()
{
	// TODO: �׷ׂ̏���

	// �U��
	mVibrator->Vibrate();

	// �����
	if( mStatus == SHUFFLE ){
		Shuffle();
	}

	// �`��
	DX_DRAW_BLEND("graphics\\teki\\queen\\boss4_mirror.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY, 
		D3DXCOLOR(mR, mG, mB, 1.0f) );

	// �g
	DX_DRAW("graphics\\teki\\queen\\boss4_mirror_frame.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY );
}

/************************************************************//**
*	��
****************************************************************/
void Kagami::StartShuffle()
{
	mR = 1.0f;
	mG = 1.0f;
	mB = 1.0f;
	mStatus = SHUFFLE;
	mShuffleStage = 0;
	mShuffleLoops = 0;
}

/************************************************************//**
*	��
****************************************************************/
void Kagami::StopShuffle()
{
	mStatus = STOP;
}

/************************************************************//**
*	��
****************************************************************/
void Kagami::Shuffle()
{
	switch( mShuffleStage ){
		case 0: 
			{
				mR -= KAGAMI_NIJISP;
				if( mR <= 0.5f ){
					mR = 0.5f;
					mShuffleStage = 1;
				}
				break;
			}
		case 1:
			{
				mG -= KAGAMI_NIJISP;
				if( mG <= 0.5f ){
					mG = 0.5f;
					mShuffleStage = 2;
				}
				break;
			}
		case 2:
			{
				mR += KAGAMI_NIJISP;
				if( mR >= 1.0f ){
					mR = 1.0f;
					mShuffleStage = 3;
				}
				break;
			}
		case 3:
			{
				mB -= KAGAMI_NIJISP;
				if( mB <= 0.5f ){
					mB = 0.5f;
					mShuffleStage = 4;
				}
				break;
			}
		case 4:
			{
				mG += KAGAMI_NIJISP;
				if( mG >= 1.0f ){
					mG = 1.0f;
					mShuffleStage = 5;
				}
				break;
			}
		case 5:
			{
				mR -= KAGAMI_NIJISP;
				if( mR <= 0.5f ){
					mR = 0.5f;
					mShuffleStage = 6;
				}
				break;
			}
		case 6:
			{
				mB += KAGAMI_NIJISP;
				if( mB >= 1.0f ){
					mB = 1.0f;
					mShuffleStage = 7;
				}
				break;
			}
		case 7:
			{
				mR += KAGAMI_NIJISP;
				if( mR >= 1.0f ){
					mR = 1.0f;
					mShuffleStage = 0;
					mShuffleLoops++;
				}
				break;
			}
	}
}

/************************************************************//**
*	�U���J�n
****************************************************************/
void Kagami::StartVibrate()
{
	mVibrator->StartVibrate();
}

/************************************************************//**
*	\param rR ���̐F�Ɏw��
*	\param rG ���̐F�Ɏw��
*	\param rB ���̐F�Ɏw��
****************************************************************/
void Kagami::SetToColor(Color col)
{
	mR = col.r;
	mG = col.g;
	mB = col.b;
}

/************************************************************//**
*	\param st 㟂̒i�K
****************************************************************/
void Kagami::SetHibiStage(int st)
{
	mHibi->SetHibiStage(st);
}

/************************************************************//**
*	\return ���̵�޼ު�Ă̺�߰
****************************************************************/
Kagami* Kagami::Clone()
{
	Kagami* newkagami = new Kagami();
	newkagami->mR = mR;
	newkagami->mG = mG;
	newkagami->mB = mB;

	return newkagami;
}