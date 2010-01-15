#include <string>
#include <list>
#include <exception>
using namespace std;

#pragma once

#include "MapCollider.h"
#include "..\\Stage\\Map.h"

class Movable;

//! 点を指定した上で、当たり判定を行う
/****************************************************************//**
*	SuperAtariHantei()のｱﾙｺﾞﾘｽﾞﾑを使用
*	\nosubgrouping
********************************************************************/
class PointMapCollider: public MapCollider
{
	public: 

		//! 標準ｺﾝｽﾄﾗｸﾀ
		PointMapCollider( Movable* rTarget );
		//! 標準ﾃﾞｽﾄﾗｸﾀ
		~PointMapCollider();

		//! @see MapCollider
		int GetCollision(MC_SIDE rSide);
		//! @see MapCollider
		int GetAdjustedPosition(MC_SIDE rSide);
		//! @see MapCollider
		void CollisionRecognition();

		//! 当たり判定用の点の追加
		void AddCollisionPoint(MC_SIDE rSide, int rX, int rY);


	private: 
		//! 位置や速度、加速度を取得可能なﾀｰｹﾞｯﾄ
		Movable* mTarget;
		
		//! 点のリスト
		Map::HITPOINT mCollisionPointsX;
		Map::HITPOINT mCollisionPointsY;

		//! 判定の出力用
		int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
		int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ
};
