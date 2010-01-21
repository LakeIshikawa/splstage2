#pragma once

#include "Teki.h"

/*
	������������l
*/
class KariudoKen2 : public Teki
{
public:
	KariudoKen2(int rXPx, int rYPx);
	~KariudoKen2(void);

	void _Move(); // �G����

	void Move();
	void Die();
	void Draw();

	TEKI_SETUP;
	

private:
	// ϯ�ߓ����蔻���ް�
	static int sMapAtHanteiX[4][MAX_TEN]; // 2�_�F�@0- ���@1- �O
	static int sMapAtHanteiY[4][MAX_TEN];

	int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
	int mAtari[4];	 // �������Ă���׸ނ�����

	float mKgTimer;	// �^�C�}�[

	bool mSeFl;	//SE�׸�


	enum STATUS {
		ARUKI,		// ����
		WAIT1,		// �U�����O
		KOGEKI,		// �U��
		WAIT2,		// �U������
		SHINDA		// ��
	}  
	mStatus;

	enum FRAMES
	{
		FR_KAMAE,	// Ų̂��\���Ă�Ƃ�
		FR_KNDOWN,	// Ų̂��������Ă�Ƃ�
		FR_ZANZOU	// Ų̂�U���Ă�Ƃ�
	};


	// ҿ���
	void MapAtHt();
	void Ataridp();
	void HtFrame();

	// �ݒ�萔
	int KARIKEN2SX;
	int KARIKEN2SY;

	float KARIKEN2SPX;
	float KARIKEN2KGHANI;
	float KARIKEN2WTM1;
	float KARIKEN2WTM2;
};
