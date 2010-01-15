#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\ParticleEmitter\\ParticleEmitter.h"

//! 噴出す火の装置
/****************************************************************//**
*	火を出します。
*	- 画面内に入ってからN秒後に最初に発動
*	\nosubgrouping
********************************************************************/
class FireStand : public Collidable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	FireStand(int rXPx, int rYPx, float Z, bool rUpDown);
	virtual ~FireStand(void);
/*@}*/

/****************************************************************//**
*	\name ｵｰﾊﾞｰﾗｲﾄﾞするﾒｿｯﾄﾞ
********************************************************************/
/*@{*/
public:
/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/

	//! 1ﾌﾚｰﾑ処理
	virtual void Move();

	//! 火を噴出す
	void ProduceFire();

	//! 当たり対応
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

/*@}*/

protected:

	//! 描画
	void Draw();

	//! 判定長方形を調整
	void AdjustCollision();
	void FadeInCollision();
	void FadeOutCollision();


	// ﾊﾟｰﾃｨｸﾙｴﾐｯﾀ
	ParticleEmitter* mEmitter;

	// ﾀｲﾏｰ
	float mProdTimer;

	// 向き(上下)
	bool mUpDown;
	
	// ｽﾃｰﾀｽ
	enum STATUS{
		WAIT,
		FIRE
	} mStatus;

	// 当たり判定用
	float mFireTop;
	float mFireBottom;
	int flag;

	// 設定定数
	float FIRESTD_PRODTIME;
	float HIBASHIRA_HEIGHT;
	float HIBASHIRA_BASESPX;

};
