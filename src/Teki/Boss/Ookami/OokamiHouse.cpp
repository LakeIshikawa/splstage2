#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "OokamiHouse.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	初期化
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
*	所属のｵﾌﾞｼﾞｪｸﾄを消去する
****************************************************************/
OokamiHouse::~OokamiHouse()
{
	if( mPtGenerator ) delete mPtGenerator;
}

/************************************************************//**
*	\param rX 出現のX座標となる
*	Yは固定であるため、設定不可能です
****************************************************************/
void OokamiHouse::SetPosX(int rX)
{
	mX = rX;
}

/************************************************************//**
*	家が消滅ｱﾆﾒｰｼｮﾝに入り、消えていく
****************************************************************/
void OokamiHouse::Destroy()
{
	mStatus = DISAPPEARING;

	// 破片ｼﾞｪﾈﾚｰﾀを作成
	BuildParticleGenerator();
}


/************************************************************//**
*	地面から出てくる
****************************************************************/
void OokamiHouse::Appear() 
{
	if( mAppearedHeight < mSizeY ){
		mAppearedHeight += OOKAMI_HSSP;
	}
	else mAppearedHeight = mSizeY;
}

/************************************************************//**
*	消滅する
****************************************************************/
void OokamiHouse::Disappear() 
{
	// ﾌｪｰﾄﾞｱｳﾄ
	mAlpha -= 0.01f;

	// 破片飛び散らす
	if( mPtGenerator )
		mPtGenerator->Generate();

	// 消滅条件
	if( mAlpha < 0 ) GAMECONTROL->GetMobManager()->Remove(this);
}

/************************************************************//**
*	破片の生成をｽﾄｯﾌﾟさせます
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
	// 動作
	switch( mStatus ){
		case APPEARING: Appear(); break;
		case DISAPPEARING: Disappear(); break;
	}
	
	// 描画
	DX_DRAWALPHA(GetGraphicSrc(), mX, mY-mAppearedHeight, 0, 0, mSizeX, 
		mAppearedHeight, mAlpha);
}
