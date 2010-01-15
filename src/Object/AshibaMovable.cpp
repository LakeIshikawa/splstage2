#include "AshibaMovable.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
*/
AshibaMovable::AshibaMovable(int rXPx, int rYPx, float rZ, string graphic, int sizex, int sizey) : 
Ashiba(rXPx, rYPx, rZ, graphic, sizex, sizey)
{
	ZeroMemory(route, sizeof(route));

	mHaichiX = rXPx;
	mHaichiY = rYPx;

	AddRoutePoint(0, rXPx, rYPx);

	ASHIBAMOV_SP = GF("ASHIBAMOV_SP");

	mLooping = false;

	Reset();
}

/**
	標準デストラクタ
*/
AshibaMovable::~AshibaMovable()
{
	for each (RoutePoint* r in route){
		if( r )	delete r;
	}
}

/************************************************************//**
*	移動を行います。mLoopingにより、最後のノードを通過した
*	時一番目に戻るかバックで戻るかが決まります。
****************************************************************/
void AshibaMovable::Move()
{
	// 移動
	if( HasArrived() ){
		GoToNext();
	}
	_Move();

	Ashiba::Move();
}

/************************************************************//**
*	ノードの追加
****************************************************************/
void AshibaMovable::AddRoutePoint(int card, int rX, int rY)
{
	route[card] = new RoutePoint(rX, rY);
}

/************************************************************//**
*	\param rOnOff オン->足場がループして初期値に戻る\n
*				  オフ->バックして戻る
****************************************************************/
void AshibaMovable::SetLooping(bool rOnOff)
{
	mLooping = rOnOff;
}

/************************************************************//**
*	\return ﾙｰﾌﾟ用のﾉｰﾄﾞ番号
****************************************************************/
int AshibaMovable::GetLoopNodeIdx()
{
	if( this == GAMECONTROL->GetStageManager()->GetCurrentStage()
		->GetHaichi()->GetAshibaMov(0) ){
			return 0xF;
	}
	else return 0x10;
}

/************************************************************//**
*	次のノードまで移動する
****************************************************************/
void AshibaMovable::_Move()
{
	// 移動
	RoutePoint* curRp = route[mCurRPoint];

	float sax = curRp->X - mX;
	float say = curRp->Y - mY;
	
	// 長さ
	float length = sqrt(sax*sax + say*say);
	if( length != 0 ){
		// nomalize
		mSpX = (sax / length) * ASHIBAMOV_SP;
		mSpY = (say / length) * ASHIBAMOV_SP;
	}
	
	mX += mSpX;
	mY += mSpY;
}

/************************************************************//**
*	次のノードに切り替える
****************************************************************/
void AshibaMovable::GoToNext()
{
	// バックの場合はマイナス
	if( mBacking ){
		mCurRPoint--;
	}
	else{
		mCurRPoint++;
	}

	// 最後に到着

	// バックの到着
	if( mBacking && mCurRPoint <= -1 ){
		mBacking = false;
		mCurRPoint = 0;
		return;
	}

	// 前進の到着
	// -- ループの到着

	// --- パスの範囲からはみ出したら
	if( mCurRPoint >= GetLoopNodeIdx()+1 ){
		// --- ループしているわけだから、最初のノードへ
		mCurRPoint = 0;
	}

	// -- 普段の到着
	// --- これから先、ノードがなかったら
	else if( route[mCurRPoint] == NULL ){
		if( mLooping ){
			// --- 最後の足場に移動
			mCurRPoint = GetLoopNodeIdx();
		}
		else{
			// --- ループじゃない、後進する
			mCurRPoint-=2;
			if( mCurRPoint < 0 ) mCurRPoint = 0;
			mBacking = true;
		}
	}
}

/************************************************************//**
*	到着の判定
*	@return 到着したか
****************************************************************/
bool AshibaMovable::HasArrived()
{
	RoutePoint* curRp = route[mCurRPoint];

	// 左右へに行きがある
	if( mSpX > 0 && mX >= curRp->X ) return true;
	if( mSpX < 0 && mX <= curRp->X ) return true;

	// 上下に行きがある
	if( mSpY > 0 && mY >= curRp->Y ) return true;
	if( mSpY < 0 && mY <= curRp->Y ) return true;

	return false;

}

/************************************************************//**
*	再初期化
*	配置の状態に戻す。
****************************************************************/
void AshibaMovable::Reset()
{
	mX = mHaichiX;
	mY = mHaichiY - ASHIBASY + SP->CHSZY;

	mCurRPoint = 0;
	mBacking = false;
}
