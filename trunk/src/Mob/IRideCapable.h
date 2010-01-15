#pragma once

class Ashiba;
class Rect;

//! ｲﾝﾀｰﾌｪｰｽ・足場に乗れるようなMob
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IRideCapable : public virtual IPositionable
{

public:

	//! 足場に乗るための長方形の取得方法
	virtual Rect* GetRideRect() = 0;

	//! 速度の取得方法
	virtual float GetSpX() = 0;

	//! 速度の取得方法
	virtual float GetSpY() = 0;

	//! 位置の調整
	virtual void SetX(int rNewX) = 0;

	//! 位置の調整
	virtual void SetY(int rNewY) = 0;

	//! 速度の調整
	virtual void SetSpX(float rNewSpX) = 0;

	//! 速度の調整
	virtual void SetSpY(float rNewSpY) = 0;


	//! 速度の加算
	virtual void AddSpX(float rAddSpX) = 0;

	//! 乗ったときのｺｰﾙﾊﾞｯｸ
	virtual void RideResponse(Ashiba* rAshiba) = 0;

	//! 降りたときのｺｰﾙﾊﾞｯｸ
	virtual void GetOffResponse(Ashiba* rAshiba) = 0;
};
