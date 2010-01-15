#pragma once


//!	��������
/****************************************************************//**
*	�������Ԃ���۰�
*	\nosubgrouping
********************************************************************/
class SeigenJikan
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	SeigenJikan();
	~SeigenJikan(void);
/*@}*/

/****************************************************************//**
*	\name �g��ҿ���
********************************************************************/
/*@{*/
	//! ���Ԃ��o������
	void Process();
/*@}*/

	//�ð�ޖ���MAX����
	void SetMaxJikan(float rSeigenjikan);

	//����
	float GetRemainingTime();
	float GetMaxJikan();

	//�������Խ���(ON)
	void SeigenJikanOn();
	//�������Խį��(OFF)
	void SeigenJikanOff();

	//��������ؾ��
	void SeigenJikanReset();

	
protected:

	float mTimer;

	//MAX����
	float mMax;
	//ON�׸�
	bool mTimeFl;

	//TIME UP
	float mTimeUpTimer;

};
