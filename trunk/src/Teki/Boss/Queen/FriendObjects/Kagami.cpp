#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Kagami.h"
#include "Hibi.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
Kagami::Kagami()
{
	// 設定定数
	mX = GI("KAGAMIX");
	mY = GI("KAGAMIY");
	mSizeX = GI("KAGAMISX");
	mSizeY = GI("KAGAMISY");
	KAGAMI_NIJISP = GF("KAGAMI_NIJISP");

	// (罅)ﾋﾋﾞ
	mHibi = new Hibi(this);
	GAMECONTROL->GetMobManager()->Request(mHibi, true);
	
	// 初期化
	SetToColor(Color(1.0f, 1.0f, 1.0f));
	mStatus = STOP;
	mZ = -0.5f;
	mVibrator = new Vibrator(3, 1.0f, 1.0f);
}

/************************************************************//**
*　所属のｵﾌﾞｼﾞｪｸﾄを開放する
****************************************************************/
Kagami::~Kagami()
{
	if( mVibrator ) delete mVibrator;
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝと描画を行う
****************************************************************/
void Kagami::Move()
{
	// TODO: ｷﾗｷﾗの処理

	// 振動
	mVibrator->Vibrate();

	// ｼｬｯﾌﾙ
	if( mStatus == SHUFFLE ){
		Shuffle();
	}

	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// 描画
	DX_DRAW_BLEND("graphics\\teki\\queen\\boss4_mirror.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY, 
		D3DXCOLOR(mR, mG, mB, 1.0f) );

	// 枠
	DX_DRAW("graphics\\teki\\queen\\boss4_mirror_frame.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY );
}

/************************************************************//**
*	虹
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
*	虹
****************************************************************/
void Kagami::StopShuffle()
{
	mStatus = STOP;
	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_kettei.wav");

}

/************************************************************//**
*	虹
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
*	振動開始
****************************************************************/
void Kagami::StartVibrate()
{
	mVibrator->StartVibrate();
}

/************************************************************//**
*	\param rR この色に指定
*	\param rG この色に指定
*	\param rB この色に指定
****************************************************************/
void Kagami::SetToColor(Color col)
{
	mR = col.r;
	mG = col.g;
	mB = col.b;
}

/************************************************************//**
*	\param st 罅の段階
****************************************************************/
void Kagami::SetHibiStage(int st)
{
	mHibi->SetHibiStage(st);
}

/************************************************************//**
*	死ね
****************************************************************/
void Kagami::JumpingDie()
{
	mSpX = -GF("SHINIPATT_SPX");
	mAccX = 0;
	mSpY = -GF("SHINIPATT_SHOSP");
	mAccY = SP->GRAVITY;
}


/************************************************************//**
*	\return このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰ
****************************************************************/
Kagami* Kagami::Clone()
{
	Kagami* newkagami = new Kagami();
	newkagami->mR = mR;
	newkagami->mG = mG;
	newkagami->mB = mB;

	return newkagami;
}