#pragma once

#include "..\\..\\Teki.h"
#include "ThrowApple.h"

#include <list>

/*
	�{�X�̖���
*/
class Majo : public Teki
{
public:

	// ��{
	enum STATUS{
		WIN,
		WINBACK,
		WINDAMAGE,
		DOOR,
		DOORTHROW,
		DOORTHROWEND,
		DOOREXIT,
		DOORDAMAGE,
		DIYING,
		DEAD
	};


	Majo();
	~Majo();

	void _Move(); // �G����

	TEKI_SETUP;

	// �C���^�[�t�F�[�X
	void InflictDamage();
	void Activate();

	// ٰ��
	void MapAtHt();

	void DousaEnd();

	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	void DieIfGamenGai() {}

	void KobitoDied();

	int GetEntPt() { return mEntPt; }
	STATUS GetStatus() { return mStatus; }

	static Map::HITPOINT sMapAtHanteiX; // 2�_�F�@0- ���@1- �O
	static Map::HITPOINT sMapAtHanteiY;

	static int sShutugenX[5];
	static int sShutugenY[5];

	static int sRingoX[5];
	static int sRingoY[5];

	static float sDieSpX[5];


	
private:

	// �o���n��I��
	void SelectEntPoint();

	void RollingAppleCreate(int rXPx, int rYPx, int rType);
	void ThrowAppleCreate(int rXPx, int rYPx, int rMuki);
	void AppleOtosu();
	void AppleThrow();
	void KobitoCreate();

	void Die();

	STATUS	mStatus;

	STATUS mSaveStatus;

	enum FRAME{
		FR_WIN,
		FR_DOOR
	};

	// �^�C�}�[
	float	mTaikiTimer;
	float	mDieTimer;

	float mSaveSpX;

	// �����蔻��p
	int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
	int mAtari[4];	 // �������Ă���׸ނ�����

	Apple* mDropMe;
	ThrowApple* mThrowMe;

	int mEntPt;

	bool mKobitoOut;

	int mHp;

	// �ݒ�萔
	int MAJOSX;
	int MAJOSY;
	float MAJO_ARUKI_SPX;

	bool mActive;
	bool dmgFlag;
	
};
