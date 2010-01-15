#pragma once

#include "Teki.h"

class KumoPink : public Teki
{
public:
	KumoPink(int rXPx, int rYPx);
	~KumoPink(void);

	void _Move(); // �G����
	
	TEKI_SETUP;

	void CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId);

	enum STATUS
	{
		ITO,
		OCHI,
		ARUKI
	};

	enum FRAMES
	{
		FR_ITO,
		FR_JIYUU
	};

private:
	// ٰ��
	void MapAtHt();

	// �ϐ��Q
	static int sMapAtHanteiX[4][MAX_TEN]; // 2�_�F�@0- ���@1- �O
	static int sMapAtHanteiY[4][MAX_TEN];

	// ��{
	STATUS	mStatus;

	// ��
	int mItoNobi;
	int mItoX;
	int mItoY;

	// �ړ��p
	int		mMoveStatus; //0-��Œ�~�@1-������ 2- ���Œ�~ 3- ���
	float	mTeishiTimer;

	// �����蔻��p
	int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
	int mAtari[4];	 // �������Ă���׸ނ�����


	//�ݒ�萔
	float KPITO_SP;
	int KPITO_LEN;
	float KPTEISHI_TIME;
	float KPARUKI_SP;

};
