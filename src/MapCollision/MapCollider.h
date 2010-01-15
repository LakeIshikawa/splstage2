#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! ϯ�߂Ƃ̓�����𔻒肷�邽�߂̲���̪��
/****************************************************************//**
*	�����蔻��̱ٺ�ؽ�т�K�v���ް��𒊏ۉ�����
*	\nosubgrouping
********************************************************************/
class MapCollider
{

	public: 
	
		//! �����蔻��̖��x���l�����ł�
		/****************************************************************//**
		*	�����蔻��̎l����
		*	\nosubgrouping
		********************************************************************/
		enum MC_SIDE
		{
			MCSD_DOWN,
			MCSD_UP,
			MCSD_FRONT,
			MCSD_BACK
		};


		//! �����蔻��̏��𓾂���@
		virtual int GetCollision(MC_SIDE rSide) = 0;

		//! ��߼��� - �������������̏C�����ꂽ�ʒu��Ԃ�
		virtual int	GetAdjustedPosition(MC_SIDE rSide) { return -1; }

		//! �����蔻��̱ٺ�ؽ�т����s������@
		virtual void CollisionRecognition() = 0;
		
};
