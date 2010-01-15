#include <exception>
using namespace std;

#include "AshibaTenbin.h"
#include "..\\Management\\GameControl.h"

char* AshibaTenbin::mGraphicData[2] = 
{
	"graphics\\object\\ashibatenbinL.png",
	"graphics\\object\\ashibatenbinR.png"
};

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
AshibaTenbin::AshibaTenbin(int rXPx, int rYPx, float rZ)
{
	TENASHIBASX = GI("TENASHIBASX");
	TENASHIBASY = GI("TENASHIBASY");
	TENBIN_DFOR = GF("TENBIN_DFOR");
	TENASHIBA_MAXSP = GF("TENASHIBA_MAXSP");
	TENASHIBA_MAXSA = GI("TENASHIBA_MAXSA");
	TENASHIBA_BACKSP = GI("TENASHIBA_BACKSP");

	mZ = rZ;

	mGrapIdx = 0;

	AddTarget(GAMECONTROL->GetJiki());

	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 0, 565, 
		TENASHIBASX, TENASHIBASY);

	mHaichiX = rXPx;
	mHaichiY = rYPx - TENASHIBASY + SP->CHSZY;

	Reset();
}

/************************************************************//**
	標準デストラクタ
****************************************************************/
AshibaTenbin::~AshibaTenbin()
{}

/************************************************************//**
*	@return この足場が所属してる天秤
****************************************************************/
Tenbin* AshibaTenbin::GetTenbin() {
	return mParent;
}

/************************************************************//**
*	強制的に上昇する
****************************************************************/
void AshibaTenbin::BringUp() {
	mStatus = UP;
}

/************************************************************//**
*	強制的に落下する
****************************************************************/
void AshibaTenbin::BringDown() {
	mStatus = DOWN;
}

/************************************************************//**
*	静止(配置)状態に戻す
****************************************************************/
void AshibaTenbin::BringBack() {
	if( mStatus == STOP || mStatus == BACK ) return;

	mStatus = BACK;

	// 現在位置と静止状態の位置を取得する
	float say = mY - mHaichiY;

	if( say > 0 ){
		mBreakFl = -1; // 自分が下
	}
	else{
		mBreakFl = 1; // 自分が上
	}
}

/************************************************************//**
*	\return 乗っているものの数
****************************************************************/
int AshibaTenbin::GetRidersNum() {
	return mRiders.size();
}

/************************************************************//**
*	\param rLeftRight 0-左足場のｸﾞﾗﾌｨｯｸ 1-右足場ｸﾞﾗﾌｨｯｸ
****************************************************************/
void AshibaTenbin::SetGraphic(int rLeftRight) {
	mGrapIdx = rLeftRight;
}

/************************************************************//**
*	再初期化
*	配置の状態に戻す。
****************************************************************/
void AshibaTenbin::Reset()
{
	mX = mHaichiX;
	mY = mHaichiY;
	mBreakAcc = 0;
	mBreakFl = false;

	mStatus = STOP;
}


/************************************************************//**
*	動きと描画の処理
****************************************************************/
void AshibaTenbin::Move()
{

	// 動作
	switch( mStatus ){

		// 静止
		case STOP:
			mAccY = 0;
			mSpY = 0;
			break;

		// 落下
		case DOWN:
			mAccY = TENBIN_DFOR;
			break;

		// 上昇
		case UP:
			mAccY = -TENBIN_DFOR;
			break;
		
		// 戻る
		case BACK:

			// 現在位置と静止状態の位置を取得する
			float say = mY - mHaichiY;

			// 現在位置が「下」の場合
			if( say > 0 ){
				// -- 加速を上に向かせる
				if( mBreakFl == 1 ){
					Reset();
				}
			}
			// 現在位置が「上」の場合
			else{
				// -- 加速を下に向かせる
				if( mBreakFl == -1 ){
					Reset();
				}
			}

			// 加速の更新
			mSpY = (TENASHIBA_BACKSP) * mBreakFl;
			mAccY = 0;
			break;
	}

	mSpY += mAccY;

	// 速度上限
	if( mSpY > TENASHIBA_MAXSP ){
		mSpY = TENASHIBA_MAXSP;
	}

	mY += mSpY;

	// 上限位置
	// 現在位置と静止状態の位置を取得する
	float say = mY - mHaichiY;
	if(( fabs(say) ) > TENASHIBA_MAXSA){
		mY = mHaichiY + TENASHIBA_MAXSA*(say>0?1:-1);
	}

	// 乗客の処理
	UpdateRiders();

	// 描画
	DX_SCROLL_DRAW(mGraphicData[mGrapIdx] ,mX, mY, 0, 0, 
		TENASHIBASX, TENASHIBASY);

	// 当たり判定枠
	if(mDrawer){
		mDrawer->SetCollision(pCollision->GetCurFrame());
		mDrawer->Draw();
	}
}
