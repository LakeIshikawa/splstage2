#pragma once

class Ashiba;
class Rect;

//! ����̪���E����ɏ���悤��Mob
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IRideCapable : public virtual IPositionable
{

public:

	//! ����ɏ�邽�߂̒����`�̎擾���@
	virtual Rect* GetRideRect() = 0;

	//! ���x�̎擾���@
	virtual float GetSpX() = 0;

	//! ���x�̎擾���@
	virtual float GetSpY() = 0;

	//! �ʒu�̒���
	virtual void SetX(int rNewX) = 0;

	//! �ʒu�̒���
	virtual void SetY(int rNewY) = 0;

	//! ���x�̒���
	virtual void SetSpX(float rNewSpX) = 0;

	//! ���x�̒���
	virtual void SetSpY(float rNewSpY) = 0;


	//! ���x�̉��Z
	virtual void AddSpX(float rAddSpX) = 0;

	//! ������Ƃ��̺���ޯ�
	virtual void RideResponse(Ashiba* rAshiba) = 0;

	//! �~�肽�Ƃ��̺���ޯ�
	virtual void GetOffResponse(Ashiba* rAshiba) = 0;
};
