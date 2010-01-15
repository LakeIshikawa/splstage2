#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Kagami.h"
#include "Hibi.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*@Ý’è’è”‚ð“Ç‚Ýž‚Þ
****************************************************************/
Kagami::Kagami()
{
	// Ý’è’è”
	mX = GI("KAGAMIX");
	mY = GI("KAGAMIY");
	mSizeX = GI("KAGAMISX");
	mSizeY = GI("KAGAMISY");
	KAGAMI_NIJISP = GF("KAGAMI_NIJISP");

	// (ãŸ)ËËÞ
	mHibi = new Hibi(this);
	GAMECONTROL->GetMobManager()->Request(mHibi, true);
	
	// ‰Šú‰»
	SetToColor(Color(1.0f, 1.0f, 1.0f));
	mStatus = STOP;
	mZ = -0.5f;
	mVibrator = new Vibrator(3, 1.0f, 1.0f);
}

/************************************************************//**
*@Š‘®‚ÌµÌÞ¼Þª¸Ä‚ðŠJ•ú‚·‚é
****************************************************************/
Kagami::~Kagami()
{
	if( mVibrator ) delete mVibrator;
}

/************************************************************//**
*	±ÆÒ°¼®Ý‚Æ•`‰æ‚ðs‚¤
****************************************************************/
void Kagami::Move()
{
	// TODO: ·×·×‚Ìˆ—

	// U“®
	mVibrator->Vibrate();

	// ¼¬¯ÌÙ
	if( mStatus == SHUFFLE ){
		Shuffle();
	}

	// •`‰æ
	DX_DRAW_BLEND("graphics\\teki\\queen\\boss4_mirror.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY, 
		D3DXCOLOR(mR, mG, mB, 1.0f) );

	// ˜g
	DX_DRAW("graphics\\teki\\queen\\boss4_mirror_frame.png",
		mX + mVibrator->GetCurWidth(), mY, 0, 0, mSizeX, mSizeY );
}

/************************************************************//**
*	“ø
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
*	“ø
****************************************************************/
void Kagami::StopShuffle()
{
	mStatus = STOP;
}

/************************************************************//**
*	“ø
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
*	U“®ŠJŽn
****************************************************************/
void Kagami::StartVibrate()
{
	mVibrator->StartVibrate();
}

/************************************************************//**
*	\param rR ‚±‚ÌF‚ÉŽw’è
*	\param rG ‚±‚ÌF‚ÉŽw’è
*	\param rB ‚±‚ÌF‚ÉŽw’è
****************************************************************/
void Kagami::SetToColor(Color col)
{
	mR = col.r;
	mG = col.g;
	mB = col.b;
}

/************************************************************//**
*	\param st ãŸ‚Ì’iŠK
****************************************************************/
void Kagami::SetHibiStage(int st)
{
	mHibi->SetHibiStage(st);
}

/************************************************************//**
*	\return ‚±‚ÌµÌÞ¼Þª¸Ä‚ÌºËß°
****************************************************************/
Kagami* Kagami::Clone()
{
	Kagami* newkagami = new Kagami();
	newkagami->mR = mR;
	newkagami->mG = mG;
	newkagami->mB = mB;

	return newkagami;
}