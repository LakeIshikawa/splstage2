#include <exception>
using namespace std;

#pragma once

#include "IPositionable.h"

class Collision;

//! 当たり判定に応答できるインターフェース
/****************************************************************//**
*	当たり判定の仕方に関係なく、応答が出来るクラスへのインターフェース
*	\nosubgrouping
********************************************************************/
class ICollidable : public virtual IPositionable
{

	public: 
		//! 当たり判定応答
		/************************************************************//**
		*	ターゲットオブジェクトにぶつかったときに呼ばれるコールバック
		*	\param rCollObject ぶつかった相手
		*	\param rThisGroupID このｵﾌﾞｼﾞｪｸﾄのぶつかった部分のｸﾞﾙｰﾌﾟID
		*	\param rThisGroupID 相手ｵﾌﾞｼﾞｪｸﾄのぶつかった部分のｸﾞﾙｰﾌﾟID
		****************************************************************/
		virtual void CollisionResponse(ICollidable* rCollObject, 
			int rThisGroupId, int rOpGroupId) = 0;

		//! 現フレームの取得方法
		virtual Collision* GetCurFrame() = 0;

		// ﾀｰｹﾞｯﾄの指定
		virtual void AddTarget(ICollidable* rTarget) = 0;
		virtual void RemoveTarget(ICollidable* rTarget) = 0;
};
