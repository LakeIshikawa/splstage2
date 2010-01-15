#pragma once

#include "..\\Teki.h"
#include "..\\..\\Mob\\LightResponseAble.h"
#include "Majo.h"

/*
	ライトに反応する小人（ボス用）
*/
class LightKobito : public Teki, public LightResponseAble
{
public:
	LightKobito();
	LightKobito( Majo* parent );
	virtual ~LightKobito();

	void RunTask();

	void Fall();

	void _Move();

	void DieIfGamenGai();

	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	enum STATUS{
		WALK,
		FALL
	};

	STATUS mStatus;

protected:
	Majo* mParent;

	void Init();


	// 設定定数
	float LKOBITO_JTK;
	float LKOBITO_BOUNDTK1;
	float LKOBITO_BOUNDTK2;
};
