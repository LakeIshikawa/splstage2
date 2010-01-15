#pragma once

#include "Ashiba.h"
#include <d3dx9.h>

//! ライトを当てるときしか見えない足場
/****************************************************************//**
*	足場・照らされていないと見えないバージョン
*	\nosubgrouping
********************************************************************/
class AshibaMovable : public virtual Ashiba
{
	
private:
	//! 足場が移動するルートのノード
	class RoutePoint
	{
	public:
		RoutePoint(int rX, int rY){X = rX; Y= rY;}
		int X;
		int Y;
	};

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	AshibaMovable(int rXPx, int rYPx, float Z, string graphic, int sizex, int sizey);
	virtual ~AshibaMovable(void);
/*@}*/

	//! プロセス
	void Move();

	//! ルートノード
	void AddRoutePoint(int card, int rX, int rY);

	//! ループの設定
	void SetLooping(bool rOnOff);

	//! 配置の時の状態に戻す
	void Reset();

protected:

	//! 移動
	void _Move();

	//! 到着判定
	bool HasArrived();

	//! 次のノードに切り替える
	void GoToNext();

	//! ﾙｰﾌﾟ用のﾉｰﾄﾞを取得
	int GetLoopNodeIdx();

	// 設定定数
	float ASHIBAMOV_SP;

	RoutePoint* route[17];
	int	mCurRPoint;
	bool mLooping;
	bool mBacking;

	// 配置座標
	int mHaichiX;
	int mHaichiY;

};
