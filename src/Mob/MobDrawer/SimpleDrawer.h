#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "MobDrawer.h"
#include "IAlphaCapable.h"

class Animation;
class IPositionable;

//! 単純な描画
/****************************************************************//**
*	位置とｱﾆﾒｰｼｮﾝの情報を合わせてDXで描画を行います
*	\nosubgrouping
********************************************************************/
class SimpleDrawer : public MobDrawer
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	SimpleDrawer();

	//! 描画の方法
	void Draw();

	//! このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰを返します
	MobDrawer* Clone();


	//! ｱﾆﾒｰｼｮﾝｵﾌﾞｼﾞｪｸﾄの設定
	void SetAnimation( Animation* rAnimation );
	//! 位置取得方法の設定
	void SetPositionInfo( IPositionable* rPositionInfo );
	//! ｱﾙﾌｧ値の設定
	void SetAlphaSrc( IAlphaCapable* rAlphaCapable );


private:
	Animation* mAnimation;			//!< ｱﾆﾒｰｼｮﾝ
	IPositionable* mPositionInfo;	//!< 位置情報
	IAlphaCapable* mAlphaCapable;	//!< ｱﾙﾌｧｵﾌﾞｼﾞｪｸﾄ
};
