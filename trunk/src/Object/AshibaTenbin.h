#include <exception>
using namespace std;

#pragma once

#include "Ashiba.h"

class Tenbin;

//! �V���̑���
/****************************************************************//**
*	�V���̕����ł���A�ЂƂƂ��đ��݂��Ȃ�
*	\nosubgrouping
********************************************************************/
class AshibaTenbin: public Ashiba
{

public:	

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
	AshibaTenbin(int rXPx, int rYPx, float Z);
	virtual ~AshibaTenbin(void);
/*@}*/

	//! �e�ł���V�����擾
	Tenbin* GetTenbin();
	
	//! 1�t���[������
	void Move();

	//! �z�u�̎��̏�Ԃɖ߂�
	void Reset();

	//! �㏸�����܂��B
	void BringUp();

	//! ���������܂��B
	void BringDown();

	//! �Î~��Ԃɖ߂����Ƃ���
	void BringBack();

	//! \return ����ɏ���Ă�����̂̐��B
	int GetRidersNum();

	//! �g�p�O���t�B�b�N���w�肷��
	void SetGraphic(int rLeftRight);

	private: 

		//! �X�e�[�^�X
		enum STATUS{
			STOP,
			BACK,
			UP,
			DOWN
		} mStatus;

		Tenbin* mParent;			//!< �e
		int mHaichiX;				//!< �z�u��X���W
		int mHaichiY;				//!< �z�u��Y���W

		float mBreakAcc;			//!< �u���[�L���邽�߂̓��I�����x
		int  mBreakFl;				//!< -1=�������Î~�l�Ԃ��u���v 1=�������Î~�l�Ԃ��u��v

		// �f�[�^
		static char* mGraphicData[2];
		int mGrapIdx;

		// �ݒ�萔�Q
		int TENASHIBASX;
		int TENASHIBASY;
		float TENBIN_DFOR;
		float TENASHIBA_MAXSP;
		int TENASHIBA_MAXSA;
		int TENASHIBA_BACKSP;

};

