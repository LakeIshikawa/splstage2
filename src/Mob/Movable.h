#pragma once

#include <list>

#include "IPositionable.h"

using namespace std;

class MobManager;

/*
	画面に出てる移動可能なオブジェクトを象徴します。


*/
class Movable : public virtual IPositionable
{
	friend class MobManager;

public:
	Movable(void);
	virtual ~Movable(void) {};

	virtual void Process();

	virtual void Move() = 0;

	virtual void RunTask() = 0;

	virtual void DieIfGamenGai();

	//! 画面外によって死んだ場合、消される直前に呼ばれる
	virtual void Finalize() {}

	virtual void Build(){}

	float Z();

	
	//! 幅の取得
	virtual int GetFrameSizeX() { return mSizeX; }

	//! 縦幅の取得
	virtual int GetFrameSizeY() { return mSizeY; }

	//! X座標の取
	virtual float GetX() { return mX; }

	//! Y座標を取得
	virtual float GetY() { return mY; }

	//! 向きを取得
	virtual bool GetMuki() { return mMuki; }

	
	//! 速度ｱｸｾｽ
	virtual float GetSpX() { return mSpX; }
	virtual float GetSpY() { return mSpY; }

	//! 加速度ｱｸｾｽ
	virtual float GetAccX(){ return mAccX; }
	virtual float GetAccY(){ return mAccY; }

	
	//! ｾｯﾄ
	void SetPos(float rX, float rY) { mX = rX; mY = rY; }
	//! ｾｯﾄ
	void SetSp(float rSpX, float rSpY) { mSpX = rSpX; mSpY = rSpY; }
	//! ｾｯﾄ
	void SetAcc(float rAccX, float rAccY) { mAccX = rAccX; mAccY = rAccY; }
	//! ｾｯﾄ
	void SetFrameSizeX(int rX, int rY) { mSizeX = rX; mSizeY = rY; }
	//! ｾｯﾄ
	void SetMuki(bool rM) { mMuki = rM; }
	//! ｾｯﾄ
	void SetZ(float rZ) { mZ = rZ; }


protected:
	//変数

	// 位置
	float mX;
	float mY;

	// 物理関係
	float mSpX;
	float mSpY;
	float mAccX;
	float mAccY;

	// ｻｲｽﾞ
	int	mSizeX;
	int mSizeY;

	// 深さ
	float mZ;

	// メモリーの所属者は「MobManager」か
	bool mOwnershipTransfered;

	bool mMuki;	//0-左　1-右

	list<Movable*> mlTaskLst;

	//関数
	void AddTask(Movable* rTask);

	//! 所属者の設定
	void SetOwnershipTransfered(bool rTrueFalse);

	//! 所属者の参照
	bool IsOwnershipTransfered();
};
