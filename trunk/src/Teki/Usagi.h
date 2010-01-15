#pragma once

#include "Teki.h"

class Usagi : public Teki
{
public:
	Usagi(int rXPx, int rYPx);
	~Usagi(void);

	void _Move(); // �G����

	TEKI_SETUP;

	enum STATUS
	{
		TAIKI,
		JUMP_START,
		JUMP,
		LAND
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

	int USAGISX;
	int USAGISY;

	float UTAIKI_TIME;
	float UJUMPSTART_TIME;
	float UJMPSPX;
	float UJMPTAKASA;

};
