#include <exception>
using namespace std;

#include "..\\Mob\\Collidable.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Management\\GameControl.h"

#pragma once

//! ｱｲﾃﾑ
/****************************************************************//**
*	ﾋﾛｲﾝが取ると効果がある
*	\nosubgrouping
********************************************************************/
class Item : public Collidable
{
public: 

	//! 標準コンストラクタ
	Item( int rX, int rY );
	//! 標準デストラクタ
	virtual ~Item();

	//! 更新
	void Move();

	//! 投げる
	void Launch(float rSpX, float rSpY, bool rMuki);
	
	//! 効果
	virtual void DoEffect() = 0;

	//! ｸﾞﾗﾌｨｯｸ
	virtual string GetGraphic() = 0;
	virtual string GetEffectGraphic() = 0;

	//! なんらかの効果ｸﾞﾗﾌｨｯｸ(きらめきなど)
	virtual void CustomEffect() {}

	//! 当たり判定
	void CollisionResponse( ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId );

protected:
	PointMapCollider* mMapCollider;

};

//! ｱｲﾃﾑ
/****************************************************************//**
*	りんご・ｴﾝﾊﾟｼｰ↑
*	\nosubgrouping
********************************************************************/
class ItRingo : public Item
{
public:
	ItRingo( int rX, int rY ) : Item( rX, rY ){}
	~ItRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreEmpacy(GI("ITEM_EMPUP")); }
	string GetGraphic() { return "graphics\\item\\Apple_a.png"; }
	string GetEffectGraphic() { return "graphics\\item\\enpathy_up.png"; }
};

//! ｱｲﾃﾑ
/****************************************************************//**
*	青りんご・ﾃﾝｼｮﾝ↑
*	\nosubgrouping
********************************************************************/
class ItAoRingo : public Item
{
public:
	ItAoRingo( int rX, int rY ) : Item( rX, rY ){}
	~ItAoRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreTension(GI("ITEM_TENUP")); }
	string GetGraphic() { return "graphics\\item\\Apple_b.png"; }
	string GetEffectGraphic() { return "graphics\\item\\tension_up.png"; }
};

//! ｱｲﾃﾑ
/****************************************************************//**
*	青りんご・ﾃﾝｼｮﾝ↑
*	\nosubgrouping
********************************************************************/
class ItKinRingo : public Item
{
public:
	ItKinRingo( int rX, int rY ) : Item( rX, rY ), mAlpha(0.0f), mAlphaSp(0.03f){}
	~ItKinRingo(){}

	void DoEffect() { GAMECONTROL->GetJiki()->RestoreLife(1); }
	string GetGraphic() { return "graphics\\item\\Apple_c.png"; }
	string GetEffectGraphic() { return "graphics\\item\\1up.png"; }
	void CustomEffect() 
	{ 
		mAlpha += mAlphaSp;
		if( mAlpha >= 1.0f || mAlpha <= 0 ) mAlphaSp *= -1;
		DX_SCROLL_SCREEN_DRAW("graphics\\effect\\effectsample.png", mX-20, mY-50, 0, 0, 128, 128, mAlpha); 
	}

private: 
	float mAlpha;
	float mAlphaSp;
};
