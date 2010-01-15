#pragma once

#include "Teki.h"

/*
	������������l
*/
class KariudoKen : public Teki
{
public:
	KariudoKen(int rXPx, int rYPx);
	~KariudoKen(void);

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
	int KARIKENSX;
	int KARIKENSY;

	float KARIKENSPX;
	float KARIKENKGHANI;
	float KARIKENWTM1;
	float KARIKENWTM2;
};
