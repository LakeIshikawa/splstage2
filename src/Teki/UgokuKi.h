#pragma once

#include "Teki.h"

/*
	������
*/
class UgokuKi : public Teki
{
public:
	UgokuKi(int rXPx, int rYPx);
	~UgokuKi(void);

	void _Move(); // �G����

	TEKI_SETUP;
	

private:
	// ϯ�ߓ����蔻���ް�
	static int sMapAtHanteiX[4][MAX_TEN]; // 2�_�F�@0- ���@1- �O
	static int sMapAtHanteiY[4][MAX_TEN];

	int mShirabe[4];  // ���������Ƃ��ɁA�ǂ̈ʒu��Ԃ��i���̎��̍��W�j
	int mAtari[4];	 // �������Ă���׸ނ�����

	
	enum STATUS {
		KAKUSHI,		// �w�i�ɑ҂��\���đҋ@
		ACTION,			// �O�ɏo�ē����o��
		ARUKI			// ����
	}  
	mStatus;

	// ҿ���
	void MapAtHt();

	void CollisionResponse(Collidable* rCollObject, int rThisGroupId, int rOpGroupId);

	// �ݒ�萔
	int UGOKUKISX;
	int UGOKUKISY;

	int UGOKUKIHANI;
	float UGOKUKISPX;

};
