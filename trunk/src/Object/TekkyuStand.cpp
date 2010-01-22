#include "TekkyuStand.h"
#include "Tekkyu.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
*/
TekkyuStand::TekkyuStand(int rXPx, int rYPx, float rZ)
{
	mSizeX = GI("TEKKYUSTDSX");
	mSizeY = GI("TEKKYUSTDSY");

	mX = rXPx;
	mY = rYPx - mSizeY + SP->CHSZY;
	mZ = rZ;

	TEKKYUSTD_PRODTIME1 = GF("TEKKYUSTD_PRODTIME1");
	TEKKYUSTD_PRODTIME2 = GF("TEKKYUSTD_PRODTIME2");
	TEKKYUSTD_MAXTEKKYU = GI("TEKKYUSTD_MAXTEKKYU");
	mProdTimer = TEKKYUSTD_PRODTIME1;
}

/**
	標準デストラクタ
*/
TekkyuStand::~TekkyuStand()
{}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void TekkyuStand::Move()
{
	// 画面外の場合、ﾀｲﾏｰをﾘｾｯﾄ
	if( GAMECONTROL->GetStageManager()->GetCurrentStage()->GetMap()->IsGamenGai( mX, mY, mSizeX, mSizeY ) )
		mProdTimer = TEKKYUSTD_PRODTIME1;

	// ﾀｲﾏｰを待機
	mProdTimer -= SP->FrameTime;
	if( mProdTimer <= 0.0f && !TekkyuMaxReached() ){
		mProdTimer = TEKKYUSTD_PRODTIME2;
		ProduceTekkyu();
	}

	// 装置の描画
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void TekkyuStand::Draw()
{
	DX_SCROLL_DRAW("graphics\\object\\obj_ag_stand.png", 
		mX, mY, 0, 0, mSizeX, mSizeY);
}

/************************************************************//**
*	鉄球を産む
****************************************************************/
void TekkyuStand::ProduceTekkyu()
{
	Tekkyu* newTekkyu = new Tekkyu( mX, mY+GI("TEKKYU_STARTY"), mZ-0.5f, this );
	GAMECONTROL->GetMobManager()->Request( newTekkyu, true );
}

/************************************************************//**
*	\return true-これ以上は作らせないぞ  false-作ってて構わないわ
****************************************************************/
bool TekkyuStand::TekkyuMaxReached()
{
	return 
		GAMECONTROL->GetMobManager()->GetInScreenNumOf<Tekkyu>()==
		TEKKYUSTD_MAXTEKKYU;
}