#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\Mob\\Collidable.h"

class AnimationSet;
class SimpleDrawer;
class PointMapCollider;

//! トランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	槍で攻撃する
*	\nosubgrouping
********************************************************************/
class TrumpSoldier : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	TrumpSoldier(int rX, int rY);
	//! 初期化(実体化の直後に呼ぶ)
	void Build();

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ｸﾞﾗﾌｨｯｸの取得方法
	virtual string GetWalkGraphic() = 0;
	virtual string GetAttackGraphic() = 0;
	virtual string GetSasuGraphic() = 0;
	virtual string GetDieGraphic() = 0;

private:

	//! 死ぬ
	void Die();
	//! 反転する
	void KabeHanten();
	//! 落下
	void Fall();


	// ｱﾆﾒｰｼｮﾝｾｯﾄ
	AnimationSet* mAnimSet;
	// 描画
	SimpleDrawer* mSDrawer;
	// ﾏｯﾌﾟとの当たり判定
	PointMapCollider* mMapCollider;

	// 当たり判定のﾌﾚｰﾑ
	enum FRAMES{
		FR_NONE,
		FR_ATTACK
	};

	// ｽﾃｰﾀｽ
	enum STATUS{
		ST_WALK,
		ST_ATTACK,
		ST_DIE
	} mStatus;

	// ｱﾆﾒｰｼｮﾝ
	enum ANIM{
		AN_WALK,
		AN_ATTACK,
		AN_SASU,
		AN_HIKU,
		AN_DIE
	} mAnims;


	// 設定定数
	float TRUMPHEISP;
	int TRUMPHEIHANI;
};


//! ﾊｰﾄのトランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	槍で攻撃する
*	\nosubgrouping
********************************************************************/
class TrumpSoldierHearts : public TrumpSoldier
{
public:
	TrumpSoldierHearts(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma1_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman1_down.png"; }
};

//! ダイヤのトランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	槍で攻撃する
*	\nosubgrouping
********************************************************************/
class TrumpSoldierDiamonds : public TrumpSoldier
{
public:
	TrumpSoldierDiamonds(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma2_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman2_down.png"; }
};

//! クローバーのトランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	槍で攻撃する
*	\nosubgrouping
********************************************************************/
class TrumpSoldierClovers : public TrumpSoldier
{
public:
	TrumpSoldierClovers(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma3_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman3_down.png"; }
};

//! クローバーのトランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	槍で攻撃する
*	\nosubgrouping
********************************************************************/
class TrumpSoldierSpades : public TrumpSoldier
{
public:
	TrumpSoldierSpades(int rX, int rY) : TrumpSoldier(rX, rY){}
	
	string GetWalkGraphic() { return "graphics\\teki\\queen\\ene_tranpma4_walk.png"; }
	string GetAttackGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_atk0.png"; }
	string GetSasuGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_atk1.png"; }
	string GetDieGraphic() { return "graphics\\teki\\queen\\ene_tranpman4_down.png"; }
};