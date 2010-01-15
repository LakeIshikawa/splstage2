#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "PointMapCollider.h"
#include "..\\Management\\GameControl.h"
#include "..\\Mob\\Movable.h"

/************************************************************//**
*	標準ｺﾝｽﾄﾗｸﾀ
****************************************************************/
PointMapCollider::PointMapCollider( Movable* rTarget ) : mTarget( rTarget )
{
	// すべての点を-1に初期化
	for( int i=MCSD_DOWN; i<=MCSD_BACK; i++){
		for( int j=0; j<MAX_TEN; j++){
			mCollisionPointsX[i][j] = -1;
			mCollisionPointsY[i][j] = -1;
		}
	}
}

/************************************************************//**
*	標準ﾃﾞｽﾄﾗｸﾀ
****************************************************************/
PointMapCollider::~PointMapCollider()
{
}

/************************************************************//**
*	\param rSide 調べる方向
*	\return 調べた方向のあたり属性(SP->CHIP_XXX)
****************************************************************/
int PointMapCollider::GetCollision(MapCollider::MC_SIDE rSide) {
	return mAtari[rSide];
}

/************************************************************//**
*	\param rSide 調べる方向
*	\return 指定された方向の当たり属性が[MCCG_NONE]以外の場合,
*			あたったところの修正された座標を返す。
*			指定方向が「下、上」の場合、Y座標が返されます。
*			指定方向が「右、左」の場合、X絶対座標が返されます。
*
*	指定された方向が「MCG_NONE」の場合、返される値が未確定です。
*
*	\note 修正された位置は、ｸﾞﾗﾌｨｯｸの左上隅を象徴しています。
*		  そのまま、mY = [collider]->GetAdjustedPosition( MCSD_DOWN )
*		  のように使ってください。
****************************************************************/
int PointMapCollider::GetAdjustedPosition(MapCollider::MC_SIDE rSide) {

	switch( rSide ){

		case MCSD_DOWN: 
		case MCSD_UP:
			return mShirabe[rSide] - mCollisionPointsY[rSide][0];  break;

		case MCSD_FRONT:
		case MCSD_BACK:
			if( mTarget->GetMuki() == 0 ){ //右向き
				return mShirabe[rSide] - mCollisionPointsX[rSide][0]; break;
			}
			else{ // 左向き
				return mShirabe[rSide] - (mTarget->GetFrameSizeX() - mCollisionPointsX[rSide][0]);
			}

		default:
			GAMECONTROL->ThrowError("GetAdjustedPosition(%d)は無意味な参照です", rSide);
			return -1;
	}
}

/************************************************************//**
*	あたり判定を行います。
*	処理のため、1ﾌﾚｰﾑに一回このメソッドを呼ぶことが理想的だと
*`	思われます。
****************************************************************/
void PointMapCollider::CollisionRecognition() {
	MAP_SUPERATHT(mTarget->GetX(), mTarget->GetY(), mTarget->GetMuki(), 
		mTarget->GetSpX(), mTarget->GetSpY(), mTarget->GetAccX(), mTarget->GetAccY(), 
		mCollisionPointsX, mCollisionPointsY, mTarget->GetFrameSizeX(), mTarget->GetFrameSizeY(), 
		mAtari, mShirabe);
}

/************************************************************//**
*	\param side この点の所属方向性
*	\param rX 点のX(ｸﾞﾗﾌｨｯｸの右上隅が原点)
*	\param rY 点のY(ｸﾞﾗﾌｨｯｸの右上隅が原点)
****************************************************************/
void PointMapCollider::AddCollisionPoint(MapCollider::MC_SIDE rSide, int rX, int rY) {

	// 空いてるとこを探す
	int curidx = -1;
	while( mCollisionPointsX[rSide][++curidx] != -1 );

	mCollisionPointsX[rSide][curidx] = rX;
	mCollisionPointsY[rSide][curidx] = rY;
}

