/****************************************************************//**
*	\file Teki.h
*	敵を作るためのｲﾝﾀｰﾌｪｰｽです。
********************************************************************/
#pragma once

class Ashiba;
class Rect;

#include "..\\Mob\\LightResponseAble.h"
#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\IRideCapable.h"

/****************************************************************//**
*	\def TEKI_SETUP
*	派生ｸﾗｽのためのﾏｸﾛ
********************************************************************/
#define TEKI_SETUP \
	static int sAniData[][MAX_DATA];\
	static char sGraphicData[][MAX_NLEN];\
	static float sAniTimeData[][MAX_DATA];\
	\
	int* AnimData()		{return &sAniData[0][0];} \
	float* AniTimeData() { return &sAniTimeData[0][0];} \
	char* GraphicData() {return &sGraphicData[0][0];}

/****************************************************************//**
*	\def TBOUND_IDX
*	足場との当たり判定用の当たり図の番号。\n
*	すべての敵は、AddIndexedRectメソッドを使って、すべてのフレームに
*	番号99の長方形を追加するべき。 これがかけていると足場と当たらなく
*	なってしまいます。
********************************************************************/
#define TBOUND_IDX 99

//! 敵の基本ｸﾗｽとなります。
/****************************************************************//**
*	敵である派生ｸﾗｽはこのｸﾗｽを継承した際に、\n
*	必ずTEKI_SETUPﾏｸﾛを宣言しなければなりません。
*	\see TEKI_SETUP
*	\nosubgrouping
********************************************************************/
class Teki : public Collidable, public IRideCapable
{
public:

	static const int MAX_DATA = 20;
	static const int MAX_NLEN = 50;
	static const int MAX_TEN = 20;

	
protected:

	//! 敵の最上ｽﾃｰﾀｽ。
	/************************************************************//**
	*	このｽﾃｰﾀｽで敵が動作をするか死ぬかが決まります
	****************************************************************/
	enum BAS_STATUS
	{
		NORMAL, //!< _Moveが呼ばれます
		SHINI   //!< 死にﾊﾟﾀｰﾝが実現します
	};
	

	/************************************************************//**
	*	\name ﾗｲﾌ循環
	****************************************************************/
	/*@{*/
	Teki(void);
	virtual ~Teki(void);
	/*@}*/

	/************************************************************//**
	*	\name ｵｰﾊﾞｰﾗｲﾄﾞするﾒｿｯﾄﾞ
	****************************************************************/
	/*@{*/

	//! 派生敵の動作
	/************************************************************//**
	*	派生敵の動きを実装するﾒｿｯﾄﾞ
	*	ｱﾆﾒｰｼｮﾝを行った後に呼ばれます
	****************************************************************/	
	virtual void _Move() = 0;

	//! ｱﾆﾒｰｼｮﾝ終了ｺｰﾙﾊﾞｯｸ
	/************************************************************//**
	*	ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝが終了したときに呼ばれます。\n
	*	このﾒｿｯﾄﾞをｵｰﾊﾞｰﾗｲﾄﾞすることで、ｱﾆﾒｰｼｮﾝが終了した \n
	*	時の行動をまとめて実装することが出来ます
	****************************************************************/
	virtual void DousaEnd() {}

protected:

	//! 当たりｺｰﾙﾊﾞｯｸ
	virtual void CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId);

public:

	/*@}*/


	/************************************************************//**
	*	\name 使うﾒｿｯﾄﾞ
	*	処理に便利な機能を提供するﾒｿｯﾄﾞ。
	****************************************************************/
	/*@{*/

	//! この敵を殺します
	virtual void Die();

	//! 敵のｸﾞﾗﾌｨｯｸの描画
	void Draw();

	//! ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ指定
	void SetAnim(int rBango);

	//! ｱﾆﾒｰｼｮﾝ処理
	void Animate();

	//! 死にﾊﾟﾀｰﾝの処理
	void ShiniPattern();
	
	//! 中心座標(X)
	/************************************************************//**
	*	この敵の中心の座標を取得出来ます(X)
	*	\return 中心の座標(X)
	****************************************************************/
	int	CenterX() {return (int)mX + mSizeX/2;}

	//! 中心座標(Y)
	/************************************************************//**
	*	この敵の中心の座標を取得出来ます(Y)
	*	\return 中心の座標(Y)
	****************************************************************/
	int CenterY() {return (int)mY + mSizeY/2;}


	/*@}*/

	/************************************************************//**
	*	\name IRideCapableの実装
	****************************************************************/
	/*@{*/
	
	Rect* GetRideRect() { return (Rect*)(pCollision->GetCurFrame()->GetIndexedShape(TBOUND_IDX)); }
	float GetSpX() {return mSpX;}
	float GetSpY() {return mSpY;}
	void SetX(int rX) { mX = rX; }
	void SetY(int rY) { mY = rY; }
	void SetSpX(float rNewSpX) { mSpX = rNewSpX; }
	void SetSpY(float rNewSpY) { mSpY = rNewSpY; }
	void AddSpX(float rAddX){ mAshibaSpX = rAddX; }
	void RideResponse(Ashiba* rAshiba) { mCurAshiba = rAshiba; }
	void GetOffResponse(Ashiba* rAshiba) { mCurAshiba = NULL; }

	/*@}*/


	/************************************************************//**
	*	\name 無視するﾒｿｯﾄﾞ
	*	中間的に使われているﾒｿｯﾄﾞであり、敵を作るために不要。
	****************************************************************/
	/*@{*/
public:

	virtual int*  AnimData() = 0;
	virtual char* GraphicData() = 0;
	virtual float* AniTimeData() = 0;

	void RunTask();
	virtual void Move();

	/*@}*/

	
protected:
	/************************************************************//**
	*	\name 変数
	*	あくまでも使うことが出来ます。
	****************************************************************/
	/*@{*/

	void Finalize();
	void DisableAshibaCollision();

	bool IsGamenGai();

	BAS_STATUS mBasStatus;	//!< 基本ｽﾃｰﾀｽ

	// ｱﾆﾒｰｼｮﾝ
	int		mAniNoX;		//!< 仮のﾌﾚｰﾑ番号（ﾃﾞｰﾀを参考する番号）
	int		mAnimSet;		//!< ｱﾆﾒｰｼｮﾝﾃﾞｰﾀの一行（ｱﾆﾒｰｼｮﾝﾊﾟﾀｰﾝ指定）
	float	mAniTimer;
	int		mNo_x;			//!< 実際のﾌﾚｰﾑ番号
	bool	mDousaEnd;		//!< ｱﾆﾒｰｼｮﾝが終わったか \deprecated DousaEnd()を使用して下さい

	// 足場用
	float	mAshibaSpX;
	Ashiba* mCurAshiba;

	// 設定定数
	float SHINIPATT_SPX;
	float SHINIPATT_SHOSP;
	float SPANI;

	/*@}*/
};

/**
	\example TekiTemplate.h
	敵ｸﾗｽの継承の実例：
*/