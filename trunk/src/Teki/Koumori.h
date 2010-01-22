#pragma once

#include "Teki.h"

class Koumori : public Teki, public LightResponseAble
{
public:
	Koumori(int rXPx, int rYPx);
	~Koumori(void);

	void _Move(); // �G����

	TEKI_SETUP;
	
	// LightResponsable�̉ˋ�ҿ���
	void ResponseAka();
	void ResponseAo();
	void ResponseMidori();
	void ResponseMushoku();
	void NoLight() {}

	int GetAtHtPointX() { return Teki::CenterX(); }
	int GetAtHtPointY() { return Teki::CenterY(); }

	void RunTask();

private:
	enum STATUS
	{
		WAIT,
		MOVE,
		NIGE
	} mStatus;

	bool mIsSEStopped;

	// �֐�
	float DetermineShosoku(float rRaiseForce);
	void Nigeru();

	//! �I�[�o�[���C�h
	void Die();

	// �ݒ�萔
	int MAAI_HABA;
	float KOMORAISE;
	float KOMOSPX;
	int KOMOCHOTEN;
};
