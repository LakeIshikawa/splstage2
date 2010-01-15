#pragma once

#include "Teki.h"

class KaeruKing : public Teki
{
public:
	KaeruKing(int rXPx, int rYPx);
	~KaeruKing(void);

	void _Move(); // �G����

	TEKI_SETUP;

	enum STATUS
	{
		TAIKI,
		JUMP_START,
		JUMP
	};

private:
	// ٰ��
	void MapAtHt();

	void DieIfGamenGai();

	// �ް�
	static int sMapAtHanteiX[4][MAX_TEN]; // 2�_�F�@0- ���@1- �O
	static int sMapAtHanteiY[4][MAX_TEN];

	// ��{
	STATUS	mStatus;

	// �ړ��p
	float	mTaikiTimer;

	// �����蔻��p
	int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
	int mAtari[4];	 // �������Ă���׸ނ�����

	int KAERUKSX;
	int KAERUKSY;

	float KTAIKI_TIME;
	float KJUMPSTART_TIME;
	float KJMPSPX;
	float KJMPTAKASA;

};
