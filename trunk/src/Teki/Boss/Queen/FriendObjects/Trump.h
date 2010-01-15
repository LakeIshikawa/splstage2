#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

class Chandelier;
class ASQueenTrumpsAttack;

//! トランプ
/****************************************************************//**
*	上昇して落下する
*	\nosubgrouping
********************************************************************/
class Trump : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Trump(int rX, int rY, string rGraphic, int rZ, int rRow, ASQueenTrumpsAttack* rParent);

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);


	//! 外呼び
	void TransformToSoldier(Chandelier* rChandelier);
	//! 落ちているか
	bool HasFallen();

private:

	string mGraphic;
	int mRow;
	float mAlpha;
	float mTimer;

	ASQueenTrumpsAttack* mParent;

	enum STATUS {
		WAIT,
		APPEAR,
		THROW,
		FALL
	} mStatus;

	// 設定定数
	int FLOORY;
	int TRUMPTOPY;
	float STD_FADEIN_SP;
};
