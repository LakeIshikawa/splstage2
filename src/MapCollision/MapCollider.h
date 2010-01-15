#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! ﾏｯﾌﾟとの当たりを判定するためのｲﾝﾀｰﾌｪｰｽ
/****************************************************************//**
*	あたり判定のｱﾙｺﾞﾘｽﾞﾑや必要なﾃﾞｰﾀを抽象化する
*	\nosubgrouping
********************************************************************/
class MapCollider
{

	public: 
	
		//! 当たり判定の密度が四方向です
		/****************************************************************//**
		*	当たり判定の四方向
		*	\nosubgrouping
		********************************************************************/
		enum MC_SIDE
		{
			MCSD_DOWN,
			MCSD_UP,
			MCSD_FRONT,
			MCSD_BACK
		};


		//! 当たり判定の情報を得る方法
		virtual int GetCollision(MC_SIDE rSide) = 0;

		//! ｵﾌﾟｼｮﾅﾙ - あたった方向の修正された位置を返す
		virtual int	GetAdjustedPosition(MC_SIDE rSide) { return -1; }

		//! 当たり判定のｱﾙｺﾞﾘｽﾞﾑを実行する方法
		virtual void CollisionRecognition() = 0;
		
};
