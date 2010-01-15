#include "HitEffect.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
*/
HitEffect::HitEffect(int rXPx, int rYPx)
{

	mSizeX = GI("HITFX_SX");
	mSizeY = GI("HITFX_SY");
	mX = rXPx;
	mY = rYPx;
	mZ = -1.0f;

	// アニメーション
	mAnim = new Animation();
	mAnim->SetGraphicSource("graphics\\effect\\hiteffect.png");
	mAnim->SetAnimData( 0, 1, 2, 3, 4, -1 );
	mAnim->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, -1.0f );

	mSDrawer = new SimpleDrawer();
	mSDrawer->SetAnimation(mAnim);
	mSDrawer->SetPositionInfo(this);
}

/**
	標準デストラクタ
*/
HitEffect::~HitEffect()
{}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void HitEffect::Move()
{
	Draw();
	
	// 消去条件
	if( mAnim->GetLoopCount() == 1 )
		GAMECONTROL->GetMobManager()->Remove(this);
}

/************************************************************//**
*	描画
****************************************************************/
void HitEffect::Draw()
{
	mAnim->ElapseTime(SP->FrameTime);
	mSDrawer->Draw();
}
