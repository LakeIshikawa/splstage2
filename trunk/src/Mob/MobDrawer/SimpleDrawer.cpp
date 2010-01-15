#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "SimpleDrawer.h"
#include "..\\..\\Animation\\Animation.h"
#include "..\\IPositionable.h"
#include "..\\..\\Management\\GameControl.h"


/************************************************************//**
*	初期化
****************************************************************/
SimpleDrawer::SimpleDrawer() : 
mAnimation(NULL), mPositionInfo(NULL), mAlphaCapable(NULL)
{}


/************************************************************//**
*	標準の描画
****************************************************************/
void SimpleDrawer::Draw() 
{
	// 現在のﾌﾚｰﾑ番号の取得
	int frno = mAnimation->GetCurFrameIdx();

	// 描画
	DX_SCROLL_ROT_DRAWALPHA( mAnimation->GetGraphicSource(), 
		mPositionInfo->GetX(), mPositionInfo->GetY(), 
		frno*mPositionInfo->GetFrameSizeX(), 
		mPositionInfo->GetMuki()*mPositionInfo->GetFrameSizeY(),
		(frno+1)*mPositionInfo->GetFrameSizeX(), 
		(mPositionInfo->GetMuki()+1)*mPositionInfo->GetFrameSizeY(), 0.0f,
		mAlphaCapable ? mAlphaCapable->GetAlpha() : 1.0f);
}

/************************************************************//**
*	このｵﾌﾞｼﾞｪｸﾄのｸﾛｰﾝを作り出す
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
*	\param rAnimation ｱﾆﾒｰｼｮﾝｵﾌﾞｼﾞｪｸﾄ
*	所属者は親となり
****************************************************************/
void SimpleDrawer::SetAnimation(Animation* rAnimation) 
{
	mAnimation = rAnimation;
}

/************************************************************//**
*	\param rPositionInfo 位置情報ｵﾌﾞｼﾞｪｸﾄ
*	所属者は親となり
****************************************************************/
void SimpleDrawer::SetPositionInfo(IPositionable* rPositionInfo) 
{
	mPositionInfo = rPositionInfo;
}

/************************************************************//**
*	\param rAlphaCapable ｱﾙﾌｧｵﾌﾞｼﾞｪｸﾄ
****************************************************************/
void SimpleDrawer::SetAlphaSrc(IAlphaCapable* rAlphaCapable) 
{
	mAlphaCapable = rAlphaCapable;
}
