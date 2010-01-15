#include <exception>
using namespace std;

#pragma once

#include "Ashiba.h"

class Tenbin;

//! 天秤の足場
/****************************************************************//**
*	天秤の部分であり、ひとつとして存在しない
*	\nosubgrouping
********************************************************************/
class AshibaTenbin: public Ashiba
{

public:	

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
	AshibaTenbin(int rXPx, int rYPx, float Z);
	virtual ~AshibaTenbin(void);
/*@}*/

	//! 親である天秤を取得
	Tenbin* GetTenbin();
	
	//! 1フレーム処理
	void Move();

	//! 配置の時の状態に戻す
	void Reset();

	//! 上昇させます。
	void BringUp();

	//! 落下させます。
	void BringDown();

	//! 静止状態に戻そうとする
	void BringBack();

	//! \return 足場に乗っているものの数。
	int GetRidersNum();

	//! 使用グラフィックを指定する
	void SetGraphic(int rLeftRight);

	private: 

		//! ステータス
		enum STATUS{
			STOP,
			BACK,
			UP,
			DOWN
		} mStatus;

		Tenbin* mParent;			//!< 親
		int mHaichiX;				//!< 配置のX座標
		int mHaichiY;				//!< 配置のY座標

		float mBreakAcc;			//!< ブレーキするための動的加速度
		int  mBreakFl;				//!< -1=自分が静止様態より「下」 1=自分が静止様態より「上」

		// データ
		static char* mGraphicData[2];
		int mGrapIdx;

		// 設定定数群
		int TENASHIBASX;
		int TENASHIBASY;
		float TENBIN_DFOR;
		float TENASHIBA_MAXSP;
		int TENASHIBA_MAXSA;
		int TENASHIBA_BACKSP;

};

